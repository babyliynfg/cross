
package org.CrossApp.lib;

import java.util.concurrent.Callable;

import org.CrossApp.lib.CrossAppHelper.CrossAppHelperListener;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.ActionBar.LayoutParams;
import android.app.Activity;
import android.content.ClipboardManager;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.Toast;

import org.CrossApp.lib.CrossAppVolumeControl;
import org.CrossApp.lib.CrossAppNetWorkManager;
import org.CrossApp.lib.CrossAppDevice;

@SuppressLint("HandlerLeak")
public abstract class CrossAppActivity extends Activity implements CrossAppHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = CrossAppActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================
    
    
    private static CrossAppActivity s_pActivity;
    
	private CrossAppGLSurfaceView mGLSurfaceView;
	
	private CrossAppWebViewHelper mWebViewHelper = null;

	private static CrossAppRenderer mCrossAppRenderer;
	
    public static Handler msHandler;
   	
    public static Handler mLightHandler;

	private static FrameLayout frame;
	
    public static CrossAppTextField _sTextField = null;
    
    public static CrossAppTextView _sTextView = null;
    
    public static CrossAppNativeTool nativeTool;
    
    public static void setSingleTextField(CrossAppTextField text) 
    {
		_sTextField = text;
	}
    
	public static void setSingleTextView(CrossAppTextView text) 
	{
		_sTextView = text;
	}
	
	public static CrossAppActivity getContext()
	{
		return CrossAppActivity.s_pActivity;
	}
	
	public static CrossAppGLSurfaceView getGLSurfaceView()
	{
		return s_pActivity.mGLSurfaceView;
	}
	
	public static FrameLayout getFrameLayout()
	{
		return CrossAppActivity.frame;
	}
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		s_pActivity = this;

    	CrossAppVolumeControl.setContext(s_pActivity);
    	
    	CrossAppPersonList.Init(this);
    	
		CrossAppHelper.init(this, this);

		CrossAppNetWorkManager.setContext(this);
		
		CrossAppAlertView.checkAliveAlertView();
		
		new CrossAppDevice(this) {};
		
		nativeTool = new CrossAppNativeTool(this);
		
    	this.init();
    	
		this.exeHandler();
		
		 if(savedInstanceState == null)
		 {
			mWebViewHelper = new CrossAppWebViewHelper(frame);
				
			CrossAppTextField.initWithHandler();		
			CrossAppTextView.initWithHandler();		
		 }
		 else if (savedInstanceState != null)
		 {
			 CrossAppTextField.reload();
             
			 CrossAppTextView.reload();
             
			 if (savedInstanceState.containsKey("WEBVIEW"))
			 {
				 mWebViewHelper = new CrossAppWebViewHelper(frame);
                 
				 String[] strs = savedInstanceState.getStringArray("WEBVIEW");
                 
				 mWebViewHelper.setAllWebviews(strs);
			 }
			 savedInstanceState.clear();
		 }
		 
	}

	@Override
	protected void onDestroy() 
	{
		super.onDestroy();
	}
	
	@Override
	protected void onResume() 
	{
		super.onResume();
		
		if (_sTextField != null) 
		{
			_sTextField.resume();
		}
		
		if (_sTextView != null)
		{
			_sTextView.resume();
		}

		CrossAppHelper.onResume();
		this.mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		
		CrossAppHelper.onPause();
		this.mGLSurfaceView.onPause();
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		
		outState.putStringArray("WEBVIEW", mWebViewHelper.getAllWebviews());
		super.onSaveInstanceState(outState);
	}
	
    @Override
    public boolean onKeyDown(final int pKeyCode, final KeyEvent pKeyEvent)
    {
        return CrossAppGLSurfaceView.getInstance().onKeyDown(pKeyCode, pKeyEvent);
    }
    
    public void setPasteBoardStr(String sender)
    {
        Message msg=new Message();
        msg.obj = sender;
        msg.what = 0;
        msHandler.sendMessage(msg);
    }

    public String getPasteBoardStr()
    {
		Callable<String> callable = new Callable<String>() 
		{
            @SuppressLint("NewApi") @Override
            public String call() throws Exception 
            {
            	ClipboardManager clipboard =  (ClipboardManager)s_pActivity.getSystemService(Context.CLIPBOARD_SERVICE);
            	
                clipboard.getText();
                
                return clipboard.getText().toString();
            }
        };
        try {
            return CrossAppWebViewHelper.callInMainThread(callable);
        } catch (Exception e) {
        }
		return "";
    }
    
    private void toast(String str)
    {
    	System.out.println(str);

        Toast.makeText(CrossAppActivity.this, str, Toast.LENGTH_SHORT).show();
    }

	 public void onActivityResult(int requestCode, int resultCode, Intent intent)
	 {
		 nativeTool.onActivityResult(requestCode, resultCode, intent);
	 }

	 @TargetApi(11)
	private void exeHandler(){
		if(mLightHandler ==null){
			mLightHandler = new Handler(){

				 @Override
				public void handleMessage(Message msg) {					 
					 int value = msg.what;
					 WindowManager.LayoutParams lp = s_pActivity.getWindow().getAttributes();
					 lp.screenBrightness = value/255.0f;
					 s_pActivity.getWindow().setAttributes(lp);
					 
					 ContentResolver resolver = s_pActivity.getContentResolver();
					 saveBrightness(resolver,value);
				}
			 };
		 }
        if(msHandler ==null){
            msHandler = new Handler(){
            		
                @Override
                public void handleMessage(Message msg) {
                    String value = (String)msg.obj;
                    int what = msg.what;
                    ClipboardManager cmb = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
                    if(what == 0)
                    {
                    	
                        cmb.setText(value);
                    }
                }
            };
        }
	}
	
	public static void saveBrightness(ContentResolver resolver, int brightness) {
        Uri uri = android.provider.Settings.System.getUriFor("screen_brightness");
        android.provider.Settings.System.putInt(resolver, "screen_brightness",brightness);
        resolver.notifyChange(uri, null);
    }
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}

	// ===========================================================
	// Methods
	// ===========================================================
@SuppressWarnings("deprecation")
public void init()
	{
		FrameLayout framelayout = new FrameLayout(this);
		framelayout.layout(0, 0, 0, 0);
		
        this.frame = framelayout;
        this.mGLSurfaceView = this.onCreateView();
		
        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
        params.leftMargin = 0; 
    	params.rightMargin = 0;
    	params.topMargin = 0;
    	params.bottomMargin = 0;
    	
        framelayout.addView(this.mGLSurfaceView, params);

        if (isAndroidEmulator())
        {
           this.mGLSurfaceView.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);
        }
        
        this.mCrossAppRenderer = new CrossAppRenderer();
        
        this.mGLSurfaceView.setCrossAppRenderer(mCrossAppRenderer);
        
        this.setContentView(framelayout);

    }
	
	public static int dip2px(Context context, float dpValue) {
	     final float scale = context.getResources().getDisplayMetrics().density;
	     return (int) (dpValue * scale + 0.5f);
	}
	
	public static  int px2dip(Context context, float pxValue) 
    {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (pxValue / scale + 0.5f);
    }
	

    public CrossAppGLSurfaceView onCreateView() {
    	return new CrossAppGLSurfaceView(this);
    }
	
    public int getStatusBarHeight() 
    {
    	  WindowManager.LayoutParams attrs = getWindow().getAttributes();
    	  if((attrs.flags & WindowManager.LayoutParams.FLAG_FULLSCREEN) == WindowManager.LayoutParams.FLAG_FULLSCREEN)
    	  {
    		  return 0;
    	  }
    	  int result = 0;
    	  int resourceId = getResources().getIdentifier("status_bar_height", "dimen", "android");
    	  if (resourceId > 0) {
    	      result = getResources().getDimensionPixelSize(resourceId);
    	  }
    	  return result;
    }

	
   private final static boolean isAndroidEmulator() {
	   
      String product = Build.PRODUCT;
	  
      boolean isEmulator = false;
	  
      if (product != null) {
         isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
      }
	  
      Log.d(TAG, "isEmulator=" + isEmulator);
	  
      return isEmulator;
   }


}

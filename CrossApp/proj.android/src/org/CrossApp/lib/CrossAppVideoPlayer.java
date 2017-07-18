package org.CrossApp.lib;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.graphics.SurfaceTexture;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
import android.widget.FrameLayout;
import android.widget.FrameLayout.LayoutParams;

@TargetApi(14)
public class CrossAppVideoPlayer extends TextureView implements TextureView.SurfaceTextureListener{
	
	public static Map<Integer, CrossAppVideoPlayer> players = new HashMap<Integer, CrossAppVideoPlayer>() ; 
	
	public static CrossAppVideoPlayer create(int key){
		
		final CrossAppVideoPlayer player = new CrossAppVideoPlayer(CrossAppActivity.getContext()) ;
		
		CrossAppActivity.getContext().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				player.setAlpha(0);
				LayoutParams p = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT) ; 
				FrameLayout layout = (FrameLayout) CrossAppActivity.getContext().getWindow().getDecorView() ; 
				layout.addView(player, p);
			}
		});
		
		return player ; 
	}
	
	/**
	 * 设置路径
	 * @param path
	 */
	public static void setDataSource(String path , int key){
		getPlayerByKey(key).setUrl(path);
	}
	
	/**
	 * 播放
	 */
	public static void play4native(final  int key){
		
		if(players.size()>0){
			Set<Integer> keys = players.keySet() ; 
			Iterator<Integer> it = keys.iterator() ; 
			while (it.hasNext()) {
				Integer integer = (Integer) it.next();
				if (players.get(integer).getMediaPlayer().isPlaying()) {
					players.get(integer).getMediaPlayer().pause();
				}
			}
		}
		
		final CrossAppVideoPlayer player = getPlayerByKey(key) ; 
		
		CrossAppActivity.getContext().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				player.play();  
				player.setOnVideoPlayingListener(new CrossAppVideoPlayer.OnVideoPlayingListener() {
		            @Override
		            public void onVideoSizeChanged(int vWidth, int vHeight) {
		            	
		            }
		            
		            @Override
		            public void onStart() {
		            }
		            @Override
		            public void onPlaying(int duration, int percent) {
		            	//调用native 的进度方法
		            	CrossAppVideoPlayer p = getPlayerByKey(key) ;
		            	if (p.getMediaPlayer().isPlaying()) {
		            		onPeriodicTime(key, percent, duration);
						}
		            }
		            @Override
		            public void onPause() {
		            }
		            @Override
		            public void onRestart() {
		            }
		            @Override
		            public void onPlayingFinish() {
		            	//调用native 的方法
		            	onDidPlayToEndTime(key);
		            }
		            @Override
		            public void onTextureDestory() {
		                if (player != null){
		                	player.pause();
		                }
		            }
		            @Override
		            public void onFrameGet(final Bitmap bitmap) {
		            	final byte[] byts = bitmap2Bytes(bitmap) ; 
		            	//调用Native刷新方法
		            	CrossAppActivity.getContext().runOnGLThread(new Runnable() 
		            	{
							@Override
							public void run() 
							{
								if (bitmap != null) {
									onFrameAttached(key , byts , bitmap.getWidth() , bitmap.getHeight()); 
								}
							}
						});
		            	
		            }
		            
		            @Override
		            public void onBufferCached(int current) {
		            	CrossAppVideoPlayer p = getPlayerByKey(key) ;
		            	if (p.getMediaPlayer().isPlaying()) {
		            		onLoadedTime(key, current, 100);
		            	}
		            }
		            
		            @Override
		            public void onSeekChanged(MediaPlayer arg0) {
		            	onTimeJumped(key);
		            }
		            
		        });
			}
		});
		
	}
	
	/**
	 * 停止
	 */
	public static void pause4native(int key){
		getPlayerByKey(key).pause();  
	}
	
	/**
	 * 得到时长
	 * @return
	 */
	public static int getDuration(int key){
		return getPlayerByKey(key).getMediaPlayer().getDuration() ; 
	}
	
	/**
	 * 获取当前播放的点
	 * @return
	 */
	public static int  getCurrentTime(int key){
		return getPlayerByKey(key).getMediaPlayer().getCurrentPosition() ; 
	}
	
	
	public static void stop4native(int key){
		CrossAppVideoPlayer player = getPlayerByKey(key) ;
		player.stop();
	}
	
	public static void setCurrentTime4native(int current,int key){
		CrossAppVideoPlayer player = getPlayerByKey(key) ;
		player.getMediaPlayer().seekTo(current);
	}
	
	public static int[] getPresentationSize4native(int key){
		CrossAppVideoPlayer player = getPlayerByKey(key) ;
		int[] size = {player.getMediaPlayer().getVideoWidth() , player.getMediaPlayer().getVideoHeight()};
		return size ; 
	}
	
	
	public static CrossAppVideoPlayer getPlayerByKey(int key){
		CrossAppVideoPlayer player = players.get(key) ; 
		if (player == null) {
			player = create(key) ; 
			player.setKey(key);
			players.put(key, player) ; 
		}
		return player ;
	}
	
	/** 删除Map中的Player */
	public static void removeById(int key){
		players.remove(key) ; 
	}
	
	public static  native void onFrameAttached(int key , byte[] bytes, int width , int height) ; 
	
	public static native void onPeriodicTime(int key , float current, float duratuon) ; // 监听播放进度
	
	public static native void onLoadedTime(int key , float current, float duratuon) ; // 监听缓冲进度
	
	public static native void onDidPlayToEndTime(int key);// 监听播放完毕
	
	public static native void onTimeJumped(int key);// 监听快进或者慢进或者跳过某段播放
	
	
	/**  
     * 把Bitmap转Byte  
     */    
    public static byte[] bitmap2Bytes(Bitmap bm){    
    	
    	if(bm== null) return new byte[0];
    	
    	ByteBuffer imageData = ByteBuffer.allocate(bm.getRowBytes() * bm.getHeight());
    	bm.copyPixelsToBuffer(imageData);
    	
    	return imageData.array() ; 
    }    
    
	/*********************************************************************************************************************************/
	/**																			子类实现																								  ****/
	/*********************************************************************************************************************************/
	
    private String TEXTUREVIDEO_TAG = "liuguoyan";
    
    private String url;
    
    public VideoState mState;
    
    private MediaPlayer mMediaPlayer;
    
    /** 毫秒帧率  1000 / 每秒帧数 */
    private final int FRAME_RATE = 30 ; 
    
    /** 刷新进度的速率 */
    private static final int PROGRESS_RATE =100 ; 
    
    /** 刷新进度消息 */
    private static final int WHAT_PROGRESS = 0 ; 
    /** 刷新界面消息 */
    private static final int WHAT_REFRESH_FRAME = 1 ; 
    
    private int mVideoWidth;//视频宽度
    private int mVideoHeight;//视频高度
    
    private int key = -1 ; 
    
    public void setKey(int key){
    	this.key = key  ; 
    }
    public int getKey(){
    	return key ; 
    }
    public interface OnVideoPlayingListener {
        void onVideoSizeChanged(int vWidth,int vHeight);
        void onStart();
        void onPlaying(int duration, int percent);
        void onPause();
        void onRestart();
        void onPlayingFinish();
        void onTextureDestory();
        void onFrameGet(Bitmap bitmap) ;
        void onBufferCached(int percent) ; 
        void onSeekChanged(MediaPlayer mp) ; 
    }
    
    
    public MediaPlayer getMediaPlayer(){
    	return mMediaPlayer ; 
    }
    
    //播放状态
    public enum VideoState{
        init,palying,pause
    }
    
    private OnVideoPlayingListener listener;
    public void setOnVideoPlayingListener(OnVideoPlayingListener listener){
        this.listener = listener;
    }
    
    public CrossAppVideoPlayer(Context context) {
        super(context);
        init();
    }

    public CrossAppVideoPlayer(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }
    
    public CrossAppVideoPlayer(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }
    
    private void init(){
        
        CrossAppActivity.getContext().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mProgressHandler = new Handler(){
			        @Override
			        public void handleMessage(Message msg) {
			            super.handleMessage(msg);
			            if (msg.what == WHAT_PROGRESS){
			                if (listener!=null && mState == VideoState.palying){
			                    listener.onPlaying(mMediaPlayer.getDuration(),mMediaPlayer.getCurrentPosition());
			                    sendEmptyMessageDelayed(WHAT_PROGRESS,PROGRESS_RATE);
			                }
			            }else if (msg.what == WHAT_REFRESH_FRAME ) {
							//刷新帧
			            	if (mState == VideoState.palying && listener!= null) {
								listener.onFrameGet(CrossAppVideoPlayer.this.getBitmap());
			            		sendEmptyMessageDelayed(WHAT_REFRESH_FRAME, FRAME_RATE) ; 
							}
						}
			        }
			    };
			}
		});
        setSurfaceTextureListener(this);
    }
    
    public void setUrl(String url){
        this.url = url;
    }
    
    public void play(){
        if (mMediaPlayer==null ) return;
        
        try {
            mMediaPlayer.reset();
            mMediaPlayer.setDataSource(url);
            mMediaPlayer.prepare();
            mMediaPlayer.start();
            mState = VideoState.palying;
            if (listener!=null) listener.onStart();
            mMediaPlayer.setOnSeekCompleteListener(new OnSeekCompleteListener() {
				@Override
				public void onSeekComplete(MediaPlayer mp) {
					listener.onSeekChanged(mp);
				}
			});
            getPlayingProgress();
        } catch (IOException e) {
            e.printStackTrace();
            Log.e(TEXTUREVIDEO_TAG , e.toString());
        }
    }
    
    public void pause(){
        if (mMediaPlayer==null) return;
        
        if (mMediaPlayer.isPlaying()){
            mMediaPlayer.pause();
            mState = VideoState.pause;
            if (listener!=null) listener.onPause();
        }else{
            mMediaPlayer.start();
            mState = VideoState.palying;
            if (listener!=null) listener.onRestart();
            getPlayingProgress();
        }
    }
    
    public void stop(){
        if (mMediaPlayer.isPlaying()){
            mMediaPlayer.stop();
        }
    }
    
    //播放进度获取
    private void getPlayingProgress(){
        mProgressHandler.sendEmptyMessage(WHAT_PROGRESS);
        mProgressHandler.sendEmptyMessage(WHAT_REFRESH_FRAME) ; 
    }
    
    private Handler mProgressHandler = null ; 
    
    
    public boolean isPlaying(){
        return mMediaPlayer.isPlaying();
    }
    
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        Log.e(TEXTUREVIDEO_TAG,"onsurfacetexture available");
        
        if (mMediaPlayer==null){
            mMediaPlayer = new MediaPlayer();
            
            mMediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mp) {
                    //当MediaPlayer对象处于Prepared状态的时候，可以调整音频/视频的属性，如音量，播放时是否一直亮屏，循环播放等。
                    mMediaPlayer.setVolume(1f,1f);
                }
            });
            mMediaPlayer.setOnErrorListener(new MediaPlayer.OnErrorListener() {
                @Override
                public boolean onError(MediaPlayer mp, int what, int extra) {
                    return false;
                }
            });

            mMediaPlayer.setOnBufferingUpdateListener(new MediaPlayer.OnBufferingUpdateListener() {
                @Override
                public void onBufferingUpdate(MediaPlayer mp, int percent) {
                    //此方法获取的是缓冲的状态
                    if(listener != null){
                    	listener.onBufferCached(percent);
                    }
                }
            });
            
            //播放完成的监听
            mMediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                @Override
                public void onCompletion(MediaPlayer mp) {
                    mState = VideoState.init;
                    if (listener!=null) listener.onPlayingFinish();
                }
            });
            
            mMediaPlayer.setOnVideoSizeChangedListener(new MediaPlayer.OnVideoSizeChangedListener() {
                @Override
                public void onVideoSizeChanged(MediaPlayer mp, int width, int height) {
                    mVideoHeight = mMediaPlayer.getVideoHeight();
                    mVideoWidth = mMediaPlayer.getVideoWidth();
                    updatePlayerSize();
                    if (listener!=null){
                        listener.onVideoSizeChanged(mVideoWidth,mVideoHeight);
                    }
                }
            });
        }
        
        //拿到要展示的图形界面
        Surface mediaSurface = new Surface(surface);
        //把surface
        mMediaPlayer.setSurface(mediaSurface);
        mState = VideoState.palying;
        
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
    }
    
    public void updatePlayerSize(){
  	  FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) this.getLayoutParams();
        params.width = mVideoWidth ; 
        params.height = mVideoHeight ; 
        this.requestLayout();
    }
    

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        mMediaPlayer.pause();
        mMediaPlayer.stop();
        mMediaPlayer.reset();
        if (listener!=null)listener.onTextureDestory();
        return false;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
    	
    }

    
    


}

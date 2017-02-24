

package org.CrossApp.lib;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.HashMap;

import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.os.Handler;
import android.os.Message;

public class CrossAppAlertView
{
	private static CrossAppActivity context = null;

	private static HashMap<Integer, AlertView> dict = null;
	
	public final static int HANDLER_SHOW_DIALOG = 1;
	public final static int HANDLER_SHOW_EDITBOX_DIALOG = 2;
	 
	public static class AlertView
	{
		public String titile;
		public String message;
		public ArrayList<String> bottonTitles = null;
		
		public AlertView(String title, String message)
		{
			this.titile = title;
			this.message = message;
			this.bottonTitles = new ArrayList<String>();
		}
		
		public void addButton(String title)
		{
			this.bottonTitles.add(title);
		}
	}
	
	public static void createAlert(final String pTitle, final String pMessage, final int key)
	{
		if (dict == null)
    	{
    		dict = new HashMap<Integer, AlertView>();
    		context = CrossAppActivity.getContext();
    	}
		
		AlertView alertView = new AlertView(pTitle, pMessage);
		dict.put(key, alertView);
	}
	
	public static void addButton(final String pTitle, final int key)
	{
		final AlertView alertView = dict.get(key);
		if (alertView != null)
		{
			alertView.addButton(pTitle);
		}
	}
	
	private static native void onClick(int index, int key);
	public static void show(final int key) 
	{
		final AlertView alertView = dict.get(key);
		context.runOnUiThread(new Runnable() 
    	{
            @Override
            public void run()
            {
            	AlertDialog.Builder builder = new AlertDialog.Builder(context);
            	builder.setTitle(alertView.titile);
            	builder.setMessage(alertView.message);
            	
        		ArrayList<String> bottonTitles = alertView.bottonTitles;
				for (int i = 0; i < bottonTitles.size(); i++) 
				{
					String title = bottonTitles.get(i);
					final int index = i;
					
					if (index == 0)
					{
						builder.setPositiveButton(title, new DialogInterface.OnClickListener() 
	            		{
	            			@Override
	    					public void onClick(DialogInterface dialog, int which)
	    					{
	            				context.runOnGLThread(new Runnable() 
	            		    	{
	            		            @Override
	            		            public void run()
	            		            {
	            		            	CrossAppAlertView.onClick(index, key);
	            		            }
	            		    	});
	    						// TODO Auto-generated method stub
	    					}
	            		});
					}
					else if (index == 1)
					{
						builder.setNeutralButton(title, new DialogInterface.OnClickListener() 
	            		{
	            			@Override
	    					public void onClick(DialogInterface dialog, int which)
	    					{
	            				context.runOnGLThread(new Runnable() 
	            		    	{
	            		            @Override
	            		            public void run()
	            		            {
	            		            	CrossAppAlertView.onClick(index, key);
	            		            }
	            		    	});
	    						// TODO Auto-generated metho
	    					}
	            		});
					}
					else if (index == 2)
					{
						builder.setNegativeButton(title, new DialogInterface.OnClickListener() 
	            		{
	            			@Override
	    					public void onClick(DialogInterface dialog, int which)
	    					{
	            				context.runOnGLThread(new Runnable() 
	            		    	{
	            		            @Override
	            		            public void run()
	            		            {
	            		            	CrossAppAlertView.onClick(index, key);
	            		            }
	            		    	});
	    						// TODO Auto-generated method stub
	    					}
	            		});
					}
				}
        		builder.create().show();
            }
        });
	}

	public static void showEditTextDialog(final String pTitle, final String pContent, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) 
	{

	}
	
	public static class EditBoxMessage 
	{
		public String title;
		public String content;
		public int inputMode;
		public int inputFlag;
		public int returnType;
		public int maxLength;
		
		public EditBoxMessage(String title, String content, int inputMode, int inputFlag, int returnType, int maxLength)
		{
			this.content = content;
			this.title = title;
			this.inputMode = inputMode;
			this.inputFlag = inputFlag;
			this.returnType = returnType;
			this.maxLength = maxLength;
		}
	}
}

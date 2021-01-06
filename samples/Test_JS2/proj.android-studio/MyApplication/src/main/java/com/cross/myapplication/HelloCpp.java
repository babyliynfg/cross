
package com.cross.myapplication;

import android.os.Bundle;

import org.CrossApp.lib.CrossAppActivity;
import org.CrossApp.lib.CrossAppGLSurfaceView;

public class HelloCpp extends CrossAppActivity{
    static {
        System.loadLibrary("CrossApp_cpp");
    }
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
	}

    public CrossAppGLSurfaceView onCreateView() {
    	CrossAppGLSurfaceView glSurfaceView = new CrossAppGLSurfaceView(this);
    	// HelloCpp should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }


}

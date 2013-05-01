package fr.dallens.balise2;

import java.io.IOException;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.Utils;


import fr.dallens.balise2.R;


import android.os.Bundle;
import android.app.Activity;
import android.graphics.Point;
import android.view.Menu;

import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.WindowManager;

import android.util.Log;


public class Balise2Activity extends Activity implements CvCameraViewListener2	 {

	public native void initJNI(long addrImRef);
	public native int findColorsJNI(long addrImTar, long addrImOut);
	public native int findColorsJNI2(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y, long addrImOut);
	
	private boolean candlesInit = false;
	private boolean processingFrame = false;
	
    private static final String  TAG = "Balise2::Activity";
    
    private ColorBall[] colorballs = new ColorBall[4]; // array that holds the balls
    private int balID = 0; // variable to know what ball is being dragged

    private CameraBridgeViewBase mOpenCvCameraView;
    
    public void initBalls() {
        // setting the start point for the balls
        Point point1 = new Point();
        point1.x = 50;
        point1.y = 20;
        Point point2 = new Point();
        point2.x = 100;
        point2.y = 20;
        Point point3 = new Point();
        point3.x = 150;
        point3.y = 20;
        Point point4 = new Point();
        point3.x = 150;
        point3.y = 80;
        
        
                       
        // declare each ball with the ColorBall class
        colorballs[0] = new ColorBall(point1);
        colorballs[1] = new ColorBall(point2);
        colorballs[2] = new ColorBall(point3);
        colorballs[3] = new ColorBall(point4);
        
        
    }
    

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                    Log.i(TAG, "OpenCV loaded successfully");
                    candlesInit = true;
                    // Now enable camera view to start receiving frames.
                    mOpenCvCameraView.enableView();
                    System.loadLibrary("bougiesjni");
                    init();
                    break;
                default:
                    super.onManagerConnected(status);
                    break;
            }
        }
    };
    
    private void init() {
    	try {
			Mat refImMat = Utils.loadResource(Balise2Activity.this, R.drawable.balise3mini, Highgui.CV_LOAD_IMAGE_GRAYSCALE);
			Log.v("Msg", String.format("Initializing bougiesJNI %d", refImMat.type()));
			initJNI(refImMat.getNativeObjAddr());
			Log.v("Msg", "bougiesJNI initialized");
		} catch (IOException e) {
			e.printStackTrace();
		}
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.v("Msg", "bougiesJNI loaded");
        //requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.activity_balise2);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.balise2_activity_surface_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);
        
        initBalls();
    }

    @Override
    public void onPause()
    {
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
        super.onPause();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
    }

    @Override
	public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_balise2, menu);
        return true;
    }



    public void onCameraViewStarted(int width, int height) {
    }

    public void onCameraViewStopped() {
    }

    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
    	Mat output = inputFrame.rgba().clone();

    	
//    	candlesInit = false;
    	if (candlesInit && !processingFrame) {
    		processingFrame = true;
	    	Mat tarImMat = new Mat();
			Imgproc.cvtColor(inputFrame.rgba(), tarImMat, Imgproc.COLOR_BGR2GRAY);
			Log.v("Msg", String.format("processing %dx%d", tarImMat.cols(), tarImMat.rows()));
//	    	try {
//	    		tarImMat = Utils.loadResource(Balise2Activity.this, R.drawable.balise4mini, Highgui.CV_LOAD_IMAGE_GRAYSCALE);
//	    	} catch (IOException e) {
	    		
//	    	}
			// FIXME 640, 480
//			Mat imOut = new Mat(tarImMat.cols()+640, Math.max(tarImMat.rows(), 480), CvType.CV_8UC4);
//			Log.v("Msg", String.format("Finding the colors (JNI) %d %d", tarImMat.type(), imOut.type()));
			int res = findColorsJNI(tarImMat.getNativeObjAddr(), output.getNativeObjAddr());
//			int res = findColorsJNI2(colorballs[0].getX(), colorballs[0].getY(), colorballs[1].getX(), colorballs[1].getY(), colorballs[2].getX(), colorballs[2].getY(), colorballs[3].getX(), colorballs[3].getY(), output.getNativeObjAddr());
			processingFrame = false;
			Log.v("Msg", "processing done");
			if ( res==0 ) {
				Log.v("Msg", "SUCCESS");
//				Log.v("Msg", String.format("********* %d %d %d %d %d %d", imOut.type(), imOut.height(), imOut.width(), imOut.rows(), imOut.cols(), imOut.channels()));

				Mat imOut2 = new Mat();
//				Imgproc.cvtColor(tarImMat, imOut2, Imgproc.COLOR_BGR2RGBA);
				Imgproc.resize(output, imOut2, new Size(inputFrame.rgba().cols(), inputFrame.rgba().rows()));
				
//				int i = 0;
//		    	for (ColorBall ball : colorballs) {
//		    		
//		    		Core.circle(imOut2, new org.opencv.core.Point(ball.getX(), ball.getY()), 8, new Scalar(i, 0, 255-i), -2);
//		    		i+=50;
//		    	}
				
				Log.v("Msg", "converted");
				return imOut2;
			} else {
				Log.v("Msg", "FAILURE");
				return output;
			}
			
    	} else {
    		Log.v("Msg", "Displaying");
    		return output;
    	}
    }
    
    
    // events when touching the screen
    public boolean onTouchEvent(MotionEvent event) {
        int eventaction = event.getAction(); 
        
        int X = (int)event.getX(); 
        int Y = (int)event.getY(); 
        
        Log.v("Touch", String.format("Touched %d %d", X, Y));
//        System.out.println(String.format("Actiong %d", eventaction));

        switch (eventaction ) { 

        case MotionEvent.ACTION_DOWN: // touch down so check if the finger is on a ball
        	balID = 0;
        	for (ColorBall ball : colorballs) {
        		// check if inside the bounds of the ball (circle)
        		// get the center for the ball
        		int centerX = ball.getX();
        		int centerY = ball.getY();
        		
        		// calculate the radius from the touch to the center of the ball
        		double radCircle  = Math.sqrt( (double) (((centerX-X)*(centerX-X)) + (centerY-Y)*(centerY-Y)));
        		
        		// if the radius is smaller then 23 (radius of a ball is 22), then it must be on the ball
        		if (radCircle < 30){
        			balID = ball.getID();
        			System.out.println(String.format("Selected %d", balID));
                    break;
        		}

        
              }
             
             break; 


        case MotionEvent.ACTION_MOVE:   // touch drag with the ball
        	// move the balls the same as the finger
            if (balID > 0) {
            	System.out.println(String.format("Moving %d", balID));
            	colorballs[balID-1].setX(X);
            	colorballs[balID-1].setY(Y);
            }
        	
            break; 

        case MotionEvent.ACTION_UP: 
       		// touch drop - just do things here after dropping

             break; 
        } 
        // redraw the canvas
        //invalidate(); 
        return true; 
	
    }
    

 
}

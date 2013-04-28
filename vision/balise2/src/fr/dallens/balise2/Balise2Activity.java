package fr.dallens.balise2;


import java.io.IOException;

import org.opencv.core.CvType;
import org.opencv.core.Mat;
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
import android.graphics.Bitmap;
import android.view.Menu;

import android.view.SurfaceView;
import android.view.WindowManager;

import android.util.Log;

public class Balise2Activity extends Activity implements CvCameraViewListener2 {

	public native void initJNI(long addrImRef);
	public native int findColorsJNI(long addrImTar, long addrImOut);
	
	private boolean candlesInit = false;
	private boolean processingFrame = false;
	
    private static final String  TAG = "Balise2::Activity";

    private CameraBridgeViewBase mOpenCvCameraView;
    

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
    	if (candlesInit && !processingFrame) {
    		Log.v("Msg", "processing");
    		processingFrame = true;
	    	Mat tarImMat = new Mat();
//			Imgproc.cvtColor(inputFrame.rgba(), tarImMat, Imgproc.COLOR_BGR2GRAY);
	    	try {
	    		tarImMat = Utils.loadResource(Balise2Activity.this, R.drawable.balise4mini, Highgui.CV_LOAD_IMAGE_GRAYSCALE);
	    	} catch (IOException e) {
	    		
	    	}
			// FIXME 640, 480
			Mat imOut = new Mat(tarImMat.cols()+640, Math.max(tarImMat.rows(), 480), CvType.CV_8UC4);
			Log.v("Msg", String.format("Finding the colors (JNI) %d %d", tarImMat.type(), imOut.type()));
			int res = findColorsJNI(tarImMat.getNativeObjAddr(), imOut.getNativeObjAddr());
			processingFrame = false;
			Log.v("Msg", "processing done");
			if ( res==0 ) {
				Log.v("Msg", "SUCCESS");
				Log.v("Msg", String.format("********* %d %d %d %d %d %d", imOut.type(), imOut.height(), imOut.width(), imOut.rows(), imOut.cols(), imOut.channels()));
//				Bitmap bmp = Bitmap.createBitmap(imOut.cols(), imOut.rows(), Bitmap.Config.ARGB_8888); 
//				Utils.matToBitmap(imOut, bmp);
				Mat imOut2 = new Mat();
//				Imgproc.cvtColor(tarImMat, imOut2, Imgproc.COLOR_BGR2RGBA);
				Imgproc.resize(imOut, imOut2, new Size(inputFrame.rgba().cols(), inputFrame.rgba().rows()));
				Log.v("Msg", "converted");
				return imOut2;
			} else {
				Log.v("Msg", "FAILURE");
				return inputFrame.rgba();
			}
			
    	} else {
    		Log.v("Msg", "Displaying");
    		return inputFrame.rgba();
    	}
    }

 
}

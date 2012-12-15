package fr.dallens.balise2;

import java.io.IOException;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener;
import org.opencv.android.Utils;
import org.opencv.imgproc.Imgproc;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
import android.view.View;
import android.util.Log;

public class Balise2Activity extends Activity implements CvCameraViewListener, OnTouchListener {

	public enum ClickAction {
		None,
		CalibrateBlue,
		CalibrateRed,
		Distort
	}
	
    private static final String  TAG = "Balise2::Activity";

    private CameraBridgeViewBase mOpenCvCameraView;
    private Mat mRgba;
    private Mat mHsv;
    private Mat mMaskBlue;
    private Mat mMaskRed;
    
    private Mat mFakePic;
    private boolean mFaking = true; // Wether to replace the camera picture.
    
    private ClickAction mClickAction = ClickAction.None;
    
    private Scalar mColorBlue = new Scalar(0, 100, 100, 255); // TODO
    private Scalar mColorRed  = new Scalar(150, 100, 100, 255);

    private Scalar mColorRadius = new Scalar(25, 50, 50, 0);

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                    Log.i(TAG, "OpenCV loaded successfully");
            		
                    // Now enable camera view to start receiving frames.
                    mOpenCvCameraView.setOnTouchListener(Balise2Activity.this);
                    mOpenCvCameraView.enableView();
                    break;
                default:
                    super.onManagerConnected(status);
                    break;
            }
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.activity_balise2);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.balise2_activity_surface_view);
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

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Log.i(TAG, "Menu Item selected " + item);

		switch (item.getItemId()) {
		case R.id.menu_fake_picture:
			mFaking = !mFaking;
			item.setChecked(mFaking);
			break;
		case R.id.menu_calibrate_colors:
			mClickAction = ClickAction.CalibrateBlue;
			break;
		case R.id.menu_fix_distorsions:
			mClickAction = ClickAction.Distort;
			break;
		}
		
		return super.onOptionsItemSelected(item);
    }

    @Override
	public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat(height, width, CvType.CV_8UC4);
        mHsv  = new Mat(height, width, CvType.CV_8UC4);
        mMaskRed = new Mat(height, width, CvType.CV_8UC3);
        mMaskBlue = new Mat(height, width, CvType.CV_8UC3);
    }

    @Override
	public void onCameraViewStopped() {
        mRgba.release();
    }

    @Override
	public Mat onCameraFrame(Mat inputFrame) {
        if(mFaking) {
        	if(mFakePic == null) {
        		try {
        			Mat mTmp = Utils.loadResource(Balise2Activity.this, R.drawable.balise1);
        			mFakePic = new Mat();
                	Imgproc.resize(mTmp, mFakePic, inputFrame.size());
                	Imgproc.cvtColor(mFakePic, mFakePic, Imgproc.COLOR_BGR2RGB); // OpenCV format is BGR.
        		} catch (IOException e) {
        			Log.e(TAG, "Cannot load resource.", e);
        		}
        	}
        	inputFrame = mFakePic;
        }
        inputFrame.copyTo(mRgba);
        
        Imgproc.blur(mRgba, mRgba, new Size(4, 4));
        
        Imgproc.cvtColor(mRgba, mHsv, Imgproc.COLOR_RGB2HSV_FULL);
        Core.inRange(mHsv, GetLowerBound(mColorBlue), GetUpperBound(mColorBlue), mMaskBlue);
        Core.inRange(mHsv, GetLowerBound(mColorRed), GetUpperBound(mColorRed), mMaskRed);
        Core.bitwise_or(mMaskBlue, mMaskRed, mMaskBlue);
        
        if(mClickAction == ClickAction.None)
        	return mMaskBlue;
        else
        	return mRgba;
    }

    @Override
	public boolean onTouch(View view, MotionEvent event) {
        int cols = mRgba.cols();
        int rows = mRgba.rows();

        int xOffset = (mOpenCvCameraView.getWidth()  - cols) / 2;
        int yOffset = (mOpenCvCameraView.getHeight() - rows) / 2;

        int x = (int)event.getX() - xOffset;
        int y = (int)event.getY() - yOffset;

        Log.i(TAG, "Touch image coordinates: (" + x + ", " + y + ")");
        if ((x < 0) || (y < 0) || (x > cols) || (y > rows))
        	return false;
        
        switch(mClickAction) {
        case CalibrateBlue:
        	mColorBlue = new Scalar(mHsv.get(y, x));
        	mClickAction = ClickAction.CalibrateRed;
        	break;
        case CalibrateRed:
        	mColorRed = new Scalar(mHsv.get(y, x));
        	mClickAction = ClickAction.None;
        	break;
    	default:
        }
        
        return false;
    }

    public Scalar GetLowerBound(Scalar hsvColor) {
        Scalar lowerBound = new Scalar(0);

        lowerBound.val[0] = hsvColor.val[0] - mColorRadius.val[0];
        lowerBound.val[1] = hsvColor.val[1] - mColorRadius.val[1];
        lowerBound.val[2] = hsvColor.val[2] - mColorRadius.val[2];
        lowerBound.val[3] = 0;
        
        return lowerBound;
    }
    
    public Scalar GetUpperBound(Scalar hsvColor) {
        Scalar upperBound = new Scalar(0);

        upperBound.val[0] = hsvColor.val[0] + mColorRadius.val[0];
        upperBound.val[1] = hsvColor.val[1] + mColorRadius.val[1];
        upperBound.val[2] = hsvColor.val[2] + mColorRadius.val[2];
        upperBound.val[3] = 255;
        
        return upperBound;
    }
}

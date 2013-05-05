package fr.dallens.balise2;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class SelectPositionActivity extends Activity {
	
	private CommunicationRobot commRobot = new CommunicationRobot();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_select_position);
		Intent intent = getIntent();
        String addressRobot = intent.getStringExtra("addressRobot");
		commRobot.connect(addressRobot);
//		Thread commRobotThread = new Thread(commRobot);
//		commRobotThread.start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.select_position, menu);
		return true;
	}
	
	public void setPosition(int pos) {
		// Dit sur quelle balise on est
		Intent intent = new Intent(this, Balise2Activity.class);
    	intent.putExtra("pos", pos);
    	intent.putExtra("robotConnexion", commRobot);
    	startActivity(intent);

	}
	
	public void setBfPosition(View view) {
		setPosition(3);
	}
	
	public void setRfPosition(View view) {
		setPosition(4);
	}
	
	public void setBmPosition(View view) {
		setPosition(5);
	}
	
	public void setRmPosition(View view) {
		setPosition(2);
	}

}

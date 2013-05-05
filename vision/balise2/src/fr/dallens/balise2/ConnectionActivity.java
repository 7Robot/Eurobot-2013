package fr.dallens.balise2;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class ConnectionActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_connection);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.connection, menu);
		return true;
	}
	
	public void onConnect(View view) {
		Intent intent = new Intent(this, SelectPositionActivity.class);
		EditText addressRobot = (EditText) findViewById(R.id.robotAddress);
    	intent.putExtra("addressRobot", addressRobot.getText().toString());
    	startActivity(intent);
	}

}

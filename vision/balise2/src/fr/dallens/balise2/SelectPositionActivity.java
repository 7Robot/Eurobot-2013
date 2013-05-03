package fr.dallens.balise2;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class SelectPositionActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_select_position);
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

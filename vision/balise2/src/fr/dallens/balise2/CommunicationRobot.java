package fr.dallens.balise2;

import android.annotation.SuppressLint;
import android.location.Address;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Serializable;
import java.net.Socket;
import java.net.UnknownHostException;

@SuppressLint("DefaultLocale")
public class CommunicationRobot implements Runnable, Serializable {
	
	private static final long serialVersionUID = 5501070147183398491L;
	private final int robotPort = 7777;
	private transient Socket socket;
	private Candles candles;
	private String TAG = "CommR";
	
	public boolean isConnected;

	public CommunicationRobot() {
		isConnected = false;
	}
	
	public void setCandles(Candles candles) {
		// SelectPositionActivity ne possède pas d'instance de Candles
		this.candles = candles;
	}
	
	public void connect(String robotAddress) {
		Log.v(TAG, String.format("Trying connection on %s", robotAddress));
		try {
			socket = new Socket(robotAddress, robotPort);
			isConnected = true;
			Log.v(TAG, "Connected");
		} catch (UnknownHostException e) {
			e.printStackTrace();
			Log.v(TAG, "Failed to connect");
		} catch (IOException e) {
			e.printStackTrace();
			Log.v(TAG, "Failed to connect");
		}
	}

	@Override
	public void run() {
		if (!isConnected)
			return;
		
		String line = "";
		BufferedReader bufferedReader = null;
		OutputStreamWriter streamWriter = null;
		try {			
			bufferedReader = new BufferedReader( new InputStreamReader(socket.getInputStream()));
			streamWriter = new OutputStreamWriter(socket.getOutputStream());
		} catch (IOException e1) {
			e1.printStackTrace();
			Log.v(TAG, "Failed to init the streams");
			isConnected = false;
		}
		
		while (isConnected) {
			try {
				line = bufferedReader.readLine();
			} catch (IOException e) {
				e.printStackTrace();
				Log.v(TAG, "Failed to receive");
				isConnected = false;
				return;
			}
			
			// En cas d'extinction de fermeture du serveur pendant le read
			// L'exception n'est pas déclenchée, mais on obtient line==null
			// C'est n'importe quoi Java !
			if (line==null) {
				Log.v(TAG, "Error during reception");
				isConnected = false;
				return;
			}
			if (line.toLowerCase().equals("getcandles")) {
				Log.v(TAG, "getcandles");
				try {
					streamWriter.write(String.format("candles %d\n", candles.getCandlesPos()));
					streamWriter.flush();
					Log.v(TAG, "candles sent");
				} catch (IOException e) {
					e.printStackTrace();
					Log.v(TAG, "Failed to send");
					isConnected = false;
					return;
				}
			}
		}
		
	}	
	
}

package org.p2lang.gtkandroid;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import java.util.Timer;
import java.util.TimerTask;
import android.view.inputmethod.InputMethodManager;
import android.content.Context;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.util.Log;


public class DummyActivity extends Activity {

    
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.v("test","oncreate");
        setContentView(R.layout.activity_dummy);
		
    }

	
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        Log.v("test", "-------------37---------------");
        getMenuInflater().inflate(R.menu.dummy, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        Log.v("test", "-------------47---------------");
        int id = item.getItemId();
        Log.v("test", "-------------49---------------");
        if (id == R.id.action_settings) {
        	Log.v("test", "-------------51---------------");
            return true;
        }
        Log.v("test", "-------------54---------------");
        return super.onOptionsItemSelected(item);
    }
    
	public static String gtThh() {
			Log.v("test", "-------------getTime()---------------");
			return "abcdefg";
		}
	
 
    public void LoadWebSite(String url){
    
    Log.v("test", "----------------GetWebPicture, url is:" + url);
    }
}


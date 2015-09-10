package it.achdjian.forno;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;

import java.sql.Connection;

import it.achdjian.forno.runnables.Connect;
import it.achdjian.forno.runnables.RESTEnable;

/**
 * A placeholder fragment containing a simple view.
 */
public class FornoActivityFragment extends Fragment implements View.OnClickListener, CompoundButton.OnCheckedChangeListener{
	private Button connectButton;
	private Switch ovenSwitch;
	private Connect connect;

	public FornoActivityFragment() {
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState) {
		View view = inflater.inflate(R.layout.fragment_forno, container, false);
		connectButton = (Button) view.findViewById(R.id.button);
		ovenSwitch = (Switch) view.findViewById(R.id.ovenSwitch);
		ovenSwitch.setEnabled(false);
		connectButton.setOnClickListener(this);

		return view;
	}

	@Override
	public void onClick(View v) {
		if (v == connectButton){
			connect = new Connect(this);
			new Thread(connect).start();
		}

	}

	public void enable(){
		ovenSwitch.setEnabled(true);
	}

	@Override
	public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
		RESTEnable restEnable = new RESTEnable(connect.getAddress(), isChecked);
		new Thread(restEnable).start();
	}
}

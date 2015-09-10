package it.achdjian.forno.runnables;

import android.app.Activity;
import android.util.Log;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;

import it.achdjian.forno.FornoActivityFragment;
import it.achdjian.forno.rest.get.OvenVersion;

/**
 * Created by Paolo Achdjian on 09/09/15.
 * Copyright Paolo Achdjian
 */
public class Connect implements Runnable {
	private static final String TAG = Connect.class.getName();
	private boolean stop=false;
	private final FornoActivityFragment parent;
	private String address;

	public Connect(FornoActivityFragment parent) {
		this.parent = parent;
	}

	public String getAddress() {
		return address;
	}

	public void setStop(boolean stop) {
		this.stop = stop;
	}

	@Override
	public void run() {
		final List<InterfaceAddress> availableAddress = new ArrayList<>();
		try {
			Enumeration<NetworkInterface> nets = NetworkInterface.getNetworkInterfaces();
			for (NetworkInterface netInt : Collections.list(nets)) {
				if(stop){
					return;
				}
				if (netInt.isLoopback() || !netInt.isUp() || netInt.isVirtual()) {
					continue;
				}
				List<InterfaceAddress> interfaceAddresses = netInt.getInterfaceAddresses();
				for (InterfaceAddress interfaceAddress : interfaceAddresses) {
					InetAddress address = interfaceAddress.getAddress();
					if (address instanceof Inet4Address) {
						availableAddress.add(interfaceAddress);
					}
				}
			}
		} catch (SocketException e) {
			e.printStackTrace();
		}

		for (InterfaceAddress interfaceAddress : availableAddress) {
			InetAddress address = interfaceAddress.getAddress();
			String hostAddress = address.getHostAddress();
			Log.d(TAG, "address: " + hostAddress + " networkPrefixLength: " + interfaceAddress.getNetworkPrefixLength());
			String[] split = hostAddress.split("[.]");
			for (int i = 1; i <= 255; i++) {
				if(stop){
					return;
				}
				String target = split[0] + "." + split[1] + "." + split[2] + "." + i;
				if (checkTarget(target)) {
					this.address = target;
					Activity activity = parent.getActivity();
					activity.runOnUiThread(new Runnable() {
						@Override
						public void run() {
							parent.enable();
						}
					});
					return;
				}
			}
		}
	}

	private boolean checkTarget(String target) {
		Log.d(TAG, "Check if " + target);
		OvenVersion ovenVersion = new OvenVersion(target);
		Log.d(TAG, "found domusEngine at " + target + " version: " + ovenVersion);
		return ovenVersion.isValid();
	}
}

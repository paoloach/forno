package it.achdjian.forno.runnables;

import org.springframework.http.ResponseEntity;
import org.springframework.web.client.RestTemplate;

/**
 * Created by Paolo Achdjian on 10/09/15.
 * Copyright Paolo Achdjian
 */
public class RESTEnable implements Runnable {
	private static final String TAG = RESTEnable.class.getName();
	private boolean stop=false;
	private String address;
	private boolean enable;

	public RESTEnable(String address, boolean enable) {
		this.address = address;
		this.enable = enable;
	}

	@Override
	public void run() {
		RestTemplate restTemplate = new RestTemplate();
		String url = "http://" + address + ":8080/enable";
		restTemplate.put(url,enable ? "1" :"0");
	}
}

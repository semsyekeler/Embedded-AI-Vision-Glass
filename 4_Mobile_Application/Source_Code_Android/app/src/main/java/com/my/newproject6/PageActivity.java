package com.my.newproject6;

import android.app.Activity;
import android.app.*;
import android.os.*;
import android.view.*;
import android.view.View.*;
import android.widget.*;
import android.content.*;
import android.content.res.*;
import android.graphics.*;
import android.graphics.drawable.*;
import android.media.*;
import android.net.*;
import android.text.*;
import android.text.style.*;
import android.util.*;
import android.webkit.*;
import android.animation.*;
import android.view.animation.*;
import java.util.*;
import java.util.regex.*;
import java.text.*;
import org.json.*;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.speech.tts.TextToSpeech;
import android.speech.SpeechRecognizer;
import android.speech.RecognizerIntent;
import android.speech.RecognitionListener;
import android.content.SharedPreferences;
import java.util.Calendar;
import java.text.SimpleDateFormat;
import java.util.Timer;
import java.util.TimerTask;
import android.view.View;
import android.content.ClipData;
import android.content.ClipboardManager;
import com.mannan.translateapi.*;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.DialogFragment;
import android.Manifest;
import android.content.pm.PackageManager;
import android.media.AudioManager;

public class PageActivity extends  Activity { 
	
	private Timer _timer = new Timer();
	
	private boolean isListening = false;
	private String sonGelenKomut = "";
	private String sonGelenYanit = "";
	private String sunucuYaniti = "";
	private String sgkbutonla = "";
	private boolean cevrildiMi = false;
	
	private LinearLayout linear1;
	private LinearLayout linear5;
	private LinearLayout linear4;
	private SeekBar seekbar1;
	private TextView textview7;
	private LinearLayout linear2;
	private TextView textview1;
	private TextView textview2;
	private TextView textview3;
	private TextView textview4;
	private TextView textview5;
	private LinearLayout linear3;
	private TextView textview11;
	private TextView textview6;
	private TextView textview8;
	private TextView textview9;
	private TextView textview10;
	
	private BluetoothConnect bt;
	private BluetoothConnect.BluetoothConnectionListener _bt_bluetooth_connection_listener;
	private TextToSpeech tts;
	private SpeechRecognizer stt;
	private SharedPreferences sharedPref;
	private MediaRecorder recorder;
	private Calendar calendar = Calendar.getInstance();
	private RequestNetwork request;
	private RequestNetwork.RequestListener _request_request_listener;
	private TimerTask timer;
	private TranslateAPI translate;
	@Override
	protected void onCreate(Bundle _savedInstanceState) {
		super.onCreate(_savedInstanceState);
		setContentView(R.layout.page);
		initialize(_savedInstanceState);
		if (Build.VERSION.SDK_INT >= 23) {
			if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED
			|| checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED
			|| checkSelfPermission(Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_DENIED) {
				requestPermissions(new String[] {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.RECORD_AUDIO}, 1000);
			}
			else {
				initializeLogic();
			}
		}
		else {
			initializeLogic();
		}
	}
	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
		if (requestCode == 1000) {
			initializeLogic();
		}
	}
	
	private void initialize(Bundle _savedInstanceState) {
		
		linear1 = (LinearLayout) findViewById(R.id.linear1);
		linear5 = (LinearLayout) findViewById(R.id.linear5);
		linear4 = (LinearLayout) findViewById(R.id.linear4);
		seekbar1 = (SeekBar) findViewById(R.id.seekbar1);
		textview7 = (TextView) findViewById(R.id.textview7);
		linear2 = (LinearLayout) findViewById(R.id.linear2);
		textview1 = (TextView) findViewById(R.id.textview1);
		textview2 = (TextView) findViewById(R.id.textview2);
		textview3 = (TextView) findViewById(R.id.textview3);
		textview4 = (TextView) findViewById(R.id.textview4);
		textview5 = (TextView) findViewById(R.id.textview5);
		linear3 = (LinearLayout) findViewById(R.id.linear3);
		textview11 = (TextView) findViewById(R.id.textview11);
		textview6 = (TextView) findViewById(R.id.textview6);
		textview8 = (TextView) findViewById(R.id.textview8);
		textview9 = (TextView) findViewById(R.id.textview9);
		textview10 = (TextView) findViewById(R.id.textview10);
		bt = new BluetoothConnect(this);
		tts = new TextToSpeech(getApplicationContext(), null);
		stt = SpeechRecognizer.createSpeechRecognizer(this);
		sharedPref = getSharedPreferences("bluetoothIcin", Activity.MODE_PRIVATE);
		request = new RequestNetwork(this);
		
		seekbar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
			@Override
			public void onProgressChanged (SeekBar _param1, int _param2, boolean _param3) {
				final int _progressValue = _param2;
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar _param1) {
				
			}
			
			@Override
			public void onStopTrackingTouch(SeekBar _param2) {
				bt.sendData(_bt_bluetooth_connection_listener, "ledleriDegereGetir:".concat(String.valueOf((long)(seekbar1.getProgress()))), "");
			}
		});
		
		textview1.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "bluetoothKulaklik", "");
			}
		});
		
		textview2.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "ftpModu", "");
			}
		});
		
		textview3.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "yayinModu", "");
			}
		});
		
		textview4.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "normalMod", "");
			}
		});
		
		linear3.setOnLongClickListener(new View.OnLongClickListener() {
			 @Override
				public boolean onLongClick(View _view) {
				
				return true;
				}
			 });
		
		textview11.setOnLongClickListener(new View.OnLongClickListener() {
			 @Override
				public boolean onLongClick(View _view) {
				((ClipboardManager) getSystemService(getApplicationContext().CLIPBOARD_SERVICE)).setPrimaryClip(ClipData.newPlainText("clipboard", textview11.getText().toString()));
				return true;
				}
			 });
		
		textview6.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:sunucuya-yukle/", "A");
				sgkbutonla = "skaydet";
			}
		});
		
		textview8.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:ocr/", "A");
				sgkbutonla = "ocr";
			}
		});
		
		textview9.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:ocr/", "A");
				sgkbutonla = "metin çevirisi";
			}
		});
		
		textview10.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View _view) {
				bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:fotograf-analizi/", "A");
				sgkbutonla = "oanalizi";
			}
		});
		
		_bt_bluetooth_connection_listener = new BluetoothConnect.BluetoothConnectionListener() {
			@Override
			public void onConnected(String _param1, HashMap<String, Object> _param2) {
				final String _tag = _param1;
				final HashMap<String, Object> _deviceData = _param2;
				SketchwareUtil.showMessage(getApplicationContext(), "baglandi");
			}
			
			@Override
			public void onDataReceived(String _param1, byte[] _param2, int _param3) {
				final String _tag = _param1;
				final String _data = new String(_param2, 0, _param3);
				if (_data.contains("asistan")) {
					_listenings();
				}
				else {
					if (_data.contains("200")) {
						timer = new TimerTask() {
							@Override
							public void run() {
								runOnUiThread(new Runnable() {
									@Override
									public void run() {
										_wifiKapat();
									}
								});
							}
						};
						_timer.schedule(timer, (int)(50000));
					}
					else {
						
					}
				}
			}
			
			@Override
			public void onDataSent(String _param1, byte[] _param2) {
				final String _tag = _param1;
				final String _data = new String(_param2);
				SketchwareUtil.showMessage(getApplicationContext(), "veri gitti");
			}
			
			@Override
			public void onConnectionError(String _param1, String _param2, String _param3) {
				final String _tag = _param1;
				final String _connectionState = _param2;
				final String _errorMessage = _param3;
				SketchwareUtil.showMessage(getApplicationContext(), _errorMessage);
			}
			
			@Override
			public void onConnectionStopped(String _param1) {
				final String _tag = _param1;
				
			}
		};
		
		stt.setRecognitionListener(new RecognitionListener() {
			@Override
			public void onReadyForSpeech(Bundle _param1) {
			}
			@Override
			public void onBeginningOfSpeech() {
			}
			@Override
			public void onRmsChanged(float _param1) {
			}
			@Override
			public void onBufferReceived(byte[] _param1) {
			}
			@Override
			public void onEndOfSpeech() {
			}
			@Override
			public void onPartialResults(Bundle _param1) {
			}
			@Override
			public void onEvent(int _param1, Bundle _param2) {
			}
			@Override
			public void onResults(Bundle _param1) {
				final ArrayList<String> _results = _param1.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
				final String _result = _results.get(0);
				isListening = false;
				AudioManager audioManager; 
				audioManager = (AudioManager) getSystemService(AUDIO_SERVICE);
				audioManager.setMode(AudioManager.MODE_NORMAL); 
				audioManager.stopBluetoothSco();
				 audioManager.setBluetoothScoOn(false);
				_komutUygula(_result);
			}
			
			@Override
			public void onError(int _param1) {
				final String _errorMessage;
				switch (_param1) {
					case SpeechRecognizer.ERROR_AUDIO:
					_errorMessage = "audio error";
					break;
					case SpeechRecognizer.ERROR_SPEECH_TIMEOUT:
					_errorMessage = "speech timeout";
					break;
					case SpeechRecognizer.ERROR_NO_MATCH:
					_errorMessage = "speech no match";
					break;
					case SpeechRecognizer.ERROR_RECOGNIZER_BUSY:
					_errorMessage = "recognizer busy";
					break;
					case SpeechRecognizer.ERROR_INSUFFICIENT_PERMISSIONS:
					_errorMessage = "recognizer insufficient permissions";
					break;
					default:
					_errorMessage = "recognizer other error";
					break;
				}
				isListening = false;
				AudioManager audioManager; 
				audioManager = (AudioManager) getSystemService(AUDIO_SERVICE);
				audioManager.setMode(AudioManager.MODE_NORMAL); 
				audioManager.stopBluetoothSco();
				 audioManager.setBluetoothScoOn(false);
			}
		});
		
		_request_request_listener = new RequestNetwork.RequestListener() {
			@Override
			public void onResponse(String _param1, String _param2, HashMap<String, Object> _param3) {
				final String _tag = _param1;
				final String _response = _param2;
				final HashMap<String, Object> _responseHeaders = _param3;
				sunucuYaniti = _response;
				if (!sunucuYaniti.equals(sonGelenYanit)) {
					if (sgkbutonla.toLowerCase().contains("metin çevirisi")) {
						if (!cevrildiMi) {
							TranslateAPI translate = new TranslateAPI(
											Language.ENGLISH,
											Language.TURKISH,
											sunucuYaniti);
							translate.setTranslateListener(new TranslateAPI.TranslateListener() {
														@Override
														public void onSuccess(String translateText) {
												cevrildiMi = true;
									textview11.setText(translateText);
									tts.speak("çeviri yanıtı; ".concat(translateText.toLowerCase()), TextToSpeech.QUEUE_ADD, null);
														}
										
														@Override
														public void onFailure(String translateError) {
												textview11.setText(translateError);
									tts.speak("metin sorunu", TextToSpeech.QUEUE_ADD, null);
														}
											});
						}
					}
					else {
						textview11.setText(sunucuYaniti);
						if (sunucuYaniti.contains(".jpg")) {
							tts.speak("fotoğraf hazır", TextToSpeech.QUEUE_ADD, null);
						}
						else {
							tts.speak(sunucuYaniti.toLowerCase(), TextToSpeech.QUEUE_ADD, null);
						}
					}
				}
				else {
					
				}
				sonGelenYanit = sunucuYaniti;
			}
			
			@Override
			public void onErrorResponse(String _param1, String _param2) {
				final String _tag = _param1;
				final String _message = _param2;
				
			}
		};
	}
	
	private void initializeLogic() {
		bt.activateBluetooth();
		bt.startConnection(_bt_bluetooth_connection_listener, sharedPref.getString("btAddress", ""), "A");
		linear5.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)40, 0xFF37474F));
		linear4.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)40, 0xFF37474F));
		seekbar1.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFF37474F));
		textview1.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview2.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview3.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview4.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview6.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview8.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview9.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		textview10.setBackground(new GradientDrawable() { public GradientDrawable getIns(int a, int b) { this.setCornerRadius(a); this.setColor(b); return this; } }.getIns((int)255, 0xFFFAFAFA));
		timer = new TimerTask() {
			@Override
			public void run() {
				runOnUiThread(new Runnable() {
					@Override
					public void run() {
						request.startRequestNetwork(RequestNetworkController.GET, "https://akilli-gozluk-default-rtdb.firebaseio.com/sunucu_yaniti.json", "A", _request_request_listener);
					}
				});
			}
		};
		_timer.scheduleAtFixedRate(timer, (int)(0), (int)(750));
	}
	
	@Override
	protected void onActivityResult(int _requestCode, int _resultCode, Intent _data) {
		
		super.onActivityResult(_requestCode, _resultCode, _data);
		
		switch (_requestCode) {
			
			default:
			break;
		}
	}
	
	public void _startVoiceRecog () {
		AudioManager audioManager; audioManager = (AudioManager) getSystemService(AUDIO_SERVICE); audioManager.setMode(AudioManager.MODE_IN_COMMUNICATION); audioManager.startBluetoothSco(); audioManager.setBluetoothScoOn(true);
		Intent _intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
		_intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, getPackageName());
		_intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
		_intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
		stt.startListening(_intent);
	}
	
	
	public void _stopListening () {
		
	}
	
	
	public void _listenings () {
		tts.stop();
		if (isListening) {
			_stopListening();
			isListening = false;
		}
		else {
			_startVoiceRecog();
			isListening = true;
		}
	}
	
	
	public void _komutUygula (final String _komut) {
		calendar = Calendar.getInstance();
		sonGelenKomut = _komut.toLowerCase();
		SketchwareUtil.showMessage(getApplicationContext(), sonGelenKomut);
		if (sonGelenKomut.contains("kaydı başlat")) {
			FileUtil.writeFile("a", "a");
			recorder = new MediaRecorder();
			recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
			recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
			recorder.setAudioEncoder(MediaRecorder.OutputFormat.AMR_NB);
			recorder.setOutputFile("storage/emulated/0/GozlukKayitlari/KAYIT_".concat(new SimpleDateFormat("dd/MM/yyyy hh:mm:ss").format(calendar.getTime())).concat(".mp3"));
			try {
				recorder.prepare();
				recorder.start();
			} catch (Exception e) {}
			SketchwareUtil.showMessage(getApplicationContext(), "Kayıt Başladı");
		}
		else {
			if (sonGelenKomut.contains("feneri aç")) {
				bt.sendData(_bt_bluetooth_connection_listener, "ledleriDegereGetir:255", "A");
			}
			else {
				if (sonGelenKomut.contains("feneri kapat")) {
					bt.sendData(_bt_bluetooth_connection_listener, "ledleriDegereGetir:0", "A");
				}
				else {
					if (sonGelenKomut.contains("metin analizi")) {
						bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:ocr/", "A");
					}
					else {
						if (sonGelenKomut.contains("metin çevirisi")) {
							bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:ocr/", "A");
						}
						else {
							if (sonGelenKomut.contains("sunucuya kaydet")) {
								bt.sendData(_bt_bluetooth_connection_listener, "fotografiYukle:sunucuya-yukle/", "A");
							}
							else {
								
							}
						}
					}
				}
			}
		}
	}
	
	
	public void _fofo_test () {
	}
	private void fo4o() {
	}
	
	
	public void _wifiKapat () {
		bt.sendData(_bt_bluetooth_connection_listener, "wifiKapat", "B");
	}
	
	
	@Deprecated
	public void showMessage(String _s) {
		Toast.makeText(getApplicationContext(), _s, Toast.LENGTH_SHORT).show();
	}
	
	@Deprecated
	public int getLocationX(View _v) {
		int _location[] = new int[2];
		_v.getLocationInWindow(_location);
		return _location[0];
	}
	
	@Deprecated
	public int getLocationY(View _v) {
		int _location[] = new int[2];
		_v.getLocationInWindow(_location);
		return _location[1];
	}
	
	@Deprecated
	public int getRandom(int _min, int _max) {
		Random random = new Random();
		return random.nextInt(_max - _min + 1) + _min;
	}
	
	@Deprecated
	public ArrayList<Double> getCheckedItemPositionsToArray(ListView _list) {
		ArrayList<Double> _result = new ArrayList<Double>();
		SparseBooleanArray _arr = _list.getCheckedItemPositions();
		for (int _iIdx = 0; _iIdx < _arr.size(); _iIdx++) {
			if (_arr.valueAt(_iIdx))
			_result.add((double)_arr.keyAt(_iIdx));
		}
		return _result;
	}
	
	@Deprecated
	public float getDip(int _input){
		return TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, _input, getResources().getDisplayMetrics());
	}
	
	@Deprecated
	public int getDisplayWidthPixels(){
		return getResources().getDisplayMetrics().widthPixels;
	}
	
	@Deprecated
	public int getDisplayHeightPixels(){
		return getResources().getDisplayMetrics().heightPixels;
	}
	
}

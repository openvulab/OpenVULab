function getSessionIdFromApplet(){
	document.example.id.value=document.rascal.getSessionid();
	
}

function startRecordingApplet(){
	document.rascal.startRecording();
}

function stopRecordingApplet(){
	document.rascal.stopRecording();
}

function isRecordingApplet(){
	document.example.busy.value = document.rascal.isRecording();
}
#pragma warning disable CA1416 // speech - windows only
using System.Speech.AudioFormat;
using System.Speech.Synthesis;

Console.WriteLine("R.E.X. Speech Generator");

var format = new SpeechAudioFormatInfo(44100, AudioBitsPerSample.Sixteen, AudioChannel.Mono);
var speech = new SpeechSynthesizer();
speech.SelectVoiceByHints(VoiceGender.Male);

/*
SpeakToFile("intro.wav", "Hello, I am REX, the robotic experimental explorer. I am autonomous, I can move on my own, sense my environment, and use my robotic arm");
SpeakToFile("greenblock.wav", "Green Block Detected");
SpeakToFile("redblock.wav", "Red Block Detected");
SpeakToFile("blueblock.wav", "Blue Block Detected");
SpeakToFile("startmotortest.wav", "Starting Motor Test");
SpeakToFile("endmotortest.wav", "Motor Test Complete");
SpeakToFile("moveleft.wav", "Moving left");
SpeakToFile("moveright.wav", "Moving right");
SpeakToFile("moveforward.wav", "Moving forward");
SpeakToFile("movereverse.wav", "Moving in reverse");
SpeakToFile("point.wav", "point");
*/
SpeakToFile("laserdetected.wav", "Block detected by laser sensor.");
SpeakToFile("activatearm.wav","Caution, stand back. Activating robotic arm.");
SpeakToFile("servo1.wav","Activating Servo 1");
SpeakToFile("servo2.wav","Activating Servo 2");
SpeakToFile("servo3.wav","Activating Servo 3");
SpeakToFile("servo4.wav","Activating Servo 4");
SpeakToFile("servo5.wav","Activating Servo 5");
SpeakToFile("servo6.wav","Activating Servo 6");
SpeakToFile("moving.wav", "Moving to");

for (int i = 2001; i < 3001; i++)
{
    SpeakToFile($"{i}.wav",$"{i}");
}

void SpeakToFile(string filename,string text)
{
    var outFile = @"c:\rex\" + filename;
    speech.SetOutputToWaveFile(outFile, format);
    speech.Speak(text);
}

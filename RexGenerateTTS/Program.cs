#pragma warning disable CA1416 // speech - windows only
using System.Speech.AudioFormat;
using System.Speech.Synthesis;

Console.WriteLine("R.E.X. Speech Generator");

var format = new SpeechAudioFormatInfo(44100, AudioBitsPerSample.Sixteen, AudioChannel.Mono);
var speech = new SpeechSynthesizer();
speech.SelectVoiceByHints(VoiceGender.Male);

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

void SpeakToFile(string filename,string text)
{
    var outFile = @"c:\rex\" + filename;
    speech.SetOutputToWaveFile(outFile, format);
    speech.Speak(text);
}

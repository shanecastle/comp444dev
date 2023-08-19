#pragma warning disable CA1416 // speech - windows only
using System.Speech.AudioFormat;
using System.Speech.Synthesis;

Console.WriteLine("Hello, World!");

//var info = new SpeechAudioFormatInfo(6, AudioBitsPerSample.Sixteen, AudioChannel.Stereo);

//var format = new SpeechAudioFormatInfo(EncodingFormat.Pcm, 44100, 16, 2, 16000, 2, null);
var format = new SpeechAudioFormatInfo(44100, AudioBitsPerSample.Sixteen,AudioChannel.Mono);

var ss = new SpeechSynthesizer();

//ss.Volume = 100;
ss.SelectVoiceByHints(VoiceGender.Male);
ss.SetOutputToWaveFile(@"C:\REX\intro5.wav", format);
ss.Speak("Hello, I am REX, the robotic experimental explorer. I am autonomous, I can move on my own, sense my environment, and use my robotic arm");
ss.SetOutputToWaveFile(@"c:\rex\greenblock.wav");
ss.Speak("Green Block Detected");

ss.SetOutputToWaveFile(@"c:\rex\redblock.wav", format);
ss.Speak("Red Block Detected");

ss.SetOutputToWaveFile(@"c:\rex\blueblock.wav", format);
ss.Speak("Blue Block Detected");

ss.SetOutputToWaveFile(@"c:\rex\point.wav", format);
ss.Speak("point");


for (var i = 0; i <= 1000; i++)
{
    ss.SetOutputToWaveFile($"c:\\rex\\numbers\\{i}.wav", format);
    ss.Speak($"{i}");
}

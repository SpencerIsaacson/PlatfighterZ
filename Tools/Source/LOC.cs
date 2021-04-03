using System;
using System.IO;

class Program
{
	static void Main()
	{
		int line_count = 0;
		int character_count = 0;
		DirectoryInfo di = new DirectoryInfo("P:/PlatfighterZ/SourceCode/");
		
		foreach(FileInfo file in di.GetFiles("*.c",SearchOption.AllDirectories))
		{
			string[] lines = File.ReadAllLines(file.FullName);
			line_count += lines.Length;
			string text = File.ReadAllText(file.FullName);
			character_count += text.Length;
		}

		foreach(FileInfo file in di.GetFiles("*.h",SearchOption.AllDirectories))
		{
			string[] lines = File.ReadAllLines(file.FullName);
			line_count += lines.Length;
			string text = File.ReadAllText(file.FullName);
			character_count += text.Length;
		}
		
		Console.WriteLine("The game contains " + line_count + " lines and " + character_count + " characters of C code.");

		System.Diagnostics.Process pProcess = new System.Diagnostics.Process();
		pProcess.StartInfo.FileName = @"P:/PlatfighterZ/build.bat";
		pProcess.StartInfo.UseShellExecute = false;
		pProcess.StartInfo.RedirectStandardOutput = true;
		pProcess.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
		pProcess.StartInfo.CreateNoWindow = true; //not diplay a windows
		System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
		pProcess.Start();
		stopwatch.Start();
		//string output = pProcess.StandardOutput.ReadToEnd(); //The output result
		pProcess.WaitForExit();
		stopwatch.Stop();
		//Console.WriteLine(output);
		Console.WriteLine($"It takes {stopwatch.Elapsed.TotalSeconds:F3} seconds to build");
	}
}
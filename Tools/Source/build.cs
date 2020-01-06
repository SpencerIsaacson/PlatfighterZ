using System;
using System.IO;

class Program
{
	static void Main(string[] args)
	{
		System.Diagnostics.Process process = new System.Diagnostics.Process();
		process.StartInfo.FileName = @"C:\Program Files\tcc\tcc.exe";
		process.StartInfo.Arguments = "-shared P:/SGL.c";
		process.StartInfo.UseShellExecute = false;
		process.StartInfo.RedirectStandardOutput = true;
		process.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
		process.StartInfo.CreateNoWindow = true; //not diplay a windows
		process.Start();
		process.WaitForExit();
		

		Console.WriteLine(process.StandardOutput.ReadToEnd());
		
		if(process.ExitCode != 0)
		{
			Console.WriteLine("there's an issue with the C code"); //TODO replace with MUCH better reporting
			return;
		}

		process = new System.Diagnostics.Process();
		process.StartInfo.FileName = @"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\Roslyn\csc.exe";
		process.StartInfo.Arguments = @"
		-out:P:\Game.exe 
		-recurse:P:\SourceCode\*.cs 
		-optimize+ 
		-langversion:7 
		-define:Windows 
		-nologo 
		-unsafe 
		-platform:x64
		-win32icon:Assets\icon.ico";

		string[] resources =
		{
			"angry_eyes.obj", 
			"avatar", 
			"bigfist_mcpunchydude_icon.png", 
			"cube.obj", 
			"dr_meroink_icon.png",
			"face.obj",
			"jeffrey_icon.png",
			"laser.wav",
			"maestro_icon.png",
			"skin.obj",
			"skin_cylinder.obj",
			"skin_poly_colors",
			"skin_reordered.obj",
			"skin_translated.obj",
			"smile.obj",
			"teapot.obj",
			"VikingStudios.png",
			"walk",
			"icon.ico",
			"preparations.wav",
			"punch.wav",
			"weight_indices"
		};

		foreach(string resource in resources)
			process.StartInfo.Arguments += $" -resource:P:/Assets/{resource}";

		process.StartInfo.UseShellExecute = false;
		process.StartInfo.RedirectStandardOutput = true;
		process.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
		process.StartInfo.CreateNoWindow = true; //not diplay a windows
		process.Start();
		process.WaitForExit();
		string output = process.StandardOutput.ReadToEnd(); //The output result
		Console.WriteLine(output);

		if(process.ExitCode == 0 && args.Length > 0 && args[0] == "-r")
		{
			System.Diagnostics.Process game = new System.Diagnostics.Process();
			game.StartInfo.FileName = "P:/Game.exe";
			game.Start();
		}
		
	}
}
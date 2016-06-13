<?php
//echo "hello there!";
if($_GET['info'])
{
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a4" => " ",
		"a3" => " ",
		"a2" => "AlienRescue",
		"a1" => "SteakSauce"
	);
	$exhibit = $codes_array[$info];
	echo "OK!<br \>\n";
	/*$result = shell_exec($command);
	file_put_contents("exhibits.txt", $exhibit, FILE_APPEND);*/
//	$command = 'echo "raspberry" | (sudo -u pi python RPWifi.py ' . escapeshellcmd($exhibit) . ')';
	$command = 'python RPWifi.py ' . escapeshellcmd($exhibit);
//	if(substr($command,strlen($command)-1,1) == "/")
//	{
//		$command = substr($command,0,strlen($command)-1);
//	} 
	echo "<br \>\nRUN COMMAND: $command<br \>\n";
	$output = shell_exec($command);
	echo str_replace("\n","<br \>\n",$output);
	echo "<br \>\n";
}
?>

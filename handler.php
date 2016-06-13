<html>
<head>
<?php
//echo "hello there!";
if($_GET['info'])
{
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a3" => "GuessTheAnimal",
		"a2" => "BongoBonanza",
		"a1" => "NutcrackerPuppet"
	);
	$exhibit = $codes_array[$info];
	echo "OK-1<br \>\n";
//	$result = shell_exec($command);
	$command = file_put_contents("exhibits.txt", $exhibit . "\n", FILE_APPEND);
	echo "OK-2<br \>\n";
	echo $exhibit . "<br \>\n";
	echo "OK-3<br \>\n";
	echo "bytes: " . $command . "<br \>\n";
	echo "OK-4<br \>\n";

	$newURL = 'http:/' . '/130.64.95.38/slideshow.php?exhibit=' . $exhibit;

	/*$command = 'echo "raspberry" | (sudo -u pi python RPWifi.py ' . escapeshellcmd($exhibit) . ')';
	$command = 'python RPWifi.py ' . escapeshellcmd($exhibit);
	if(substr($command,strlen($command)-1,1) == "/")
	{
		$command = substr($command,0,strlen($command)-1);
	}
	echo "<br \>\nRUN COMMAND: $command<br \>\n";
	$output = shell_exec($command);
	echo str_replace("\n","<br \>\n",$output);
	echo "<br \>\n";*/
}
?>
<script language=JavaScript>window.location.href="<?php echo $newURL ?>"</script>
</head></html>

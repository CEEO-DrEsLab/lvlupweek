<?php
echo "hello there!";/*
if($_GET['info'])
{

	echo "hello";
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a2" => "AlienRescue"
		"a1" => "SteakSauce"
	);
	$exhibit = $codes_array[$info];
	echo $exhibit;
	/*$result = exec('sudo -u www-data python /var/www/html/opener.py $exhibit');*/
	/*$command = escapeshellcmd('sudo -u www-data python /var/www/html/opener.py $exhibit');*/
	/*$command = escapeshellcmd('sudo -u www-data python -m webbrowser -t "www.google.com"');
	$result = shell_exec($command);*/
	/*file_put_contents("exhibits.txt", $exhibit, FILE_APPEND);


}*/

?>

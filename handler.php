<?php
echo "hi there!<br \>\n";

if($_GET['id'])
{
  $id = strip_tags($_GET['id']);

  $codes_array = array(
    "a3" => "GuessTheAnimal",
    "a2" => "BongoBonanza",
    "a1" => "NutcrackerPuppet"
    );
  $exhibit = $codes_array[$id];
  echo "OK-2<br \>\n";
  $command = file_put_contents("/var/www/html/exhibits.txt", $exhibit);
  $newURL = 'http:/' . '/130.64.95.38/slideshow.php?exhibit=' . $exhibit;
  echo $newURL;

  if($_GET['redir'])
  {
    //If signal comes from non-Arduino: pull up webpage on source device
    header("Location: " . $newURL);
    exit;
  }
}
?>
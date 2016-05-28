<?php
if($_GET['exhibit'])

	$exhibit = strip_tags($_GET['exhibit']);
?>

<!--
	html document for media display
	by Caleb Lucas-Foley
	Jun 2016
-->
<!DOCTYPE html>

<html>
<head>
	<meta charset="utf-8">
	<title>Exhibit Not Found</title>
	<style>
	* {
		padding:0px;
		margin:0px;
	}
	html, body {
		height:100%;
	}
	body {
		color:lightgrey;
		background-color:black;
	}
	#slideshow {
		position:absolute;
		width:100%;
		left:0px;
		top:0px;
		bottom:150px;
	}
	#textbox {
		padding-left:10px;
		padding-right:10px;
		position:absolute;
		height:150px;
		bottom:0px;
	}
	</style>
	
</head>

<body>
<div id="slideshow"></div>

<div id="textbox">
	<h1 id="title">Exhibit Not Found</h1>
	<p id="description">
		Add the exhibit name as a query string.
	</p>
</div>


<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>

<script>
// Gets the exhibit name from a query string in the URL
function getExhibitName() {
	matches = RegExp('[?&]exhibit=([^&]*)').exec(window.location.search);
	return matches == null ? null : decodeURIComponent(matches[1].replace(/\+/g, ' ')); // replace + with space
}
// Sets the title of the window and the title of the description to title.txt
function setTitle(exhibitName) {
	$('title').load("Exhibits/" + exhibitName + "/title.txt");
	$('#title').load("Exhibits/" + exhibitName + "/title.txt");
}
// Sets the description contents to the contents of description.txt
function setDescription(exhibitName) {
	$('#description').load("Exhibits/" + exhibitName + "/description.txt");
}
// Load the list of image URLs to display. Note: currently not functioning
function loadImageURLs(exhibitName) {
	// console.log("running fcn");
	// $.get("Exhibits/" + exhibitName + "/images/", function(data) {
	// 	console.log(data); // Problem: Request fails.
	// })
}



// Play the videos; when complete, play the slideshow. Note: video URLs are hard-coded local URLs.
function videoPlaylist() {
	var videoURLs = ["Exhibits/AlienRescue/videos/AlienRescue.mp4", "Exhibits/Bongo%20Bonanza/videos/BongoBonanza.mp4"]/* List of github video urls */
	if (videoURLs.length > 0) {
		var slideshow = document.getElementById("slideshow");
		var video = document.createElement("video");
		video.style.marginLeft = "auto";
		video.style.marginRight = "auto";
		video.style.display = "block";
		video.style.height = "100%";
		var source = document.createElement("source");
		var videoIndex = 0;
		source.setAttribute('src', videoURLs[videoIndex]);
		video.appendChild(source);
		slideshow.appendChild(video);
		video.addEventListener('ended', nextVideo);
		video.play();
		function nextVideo() {
			video.pause();
			++videoIndex;
			if (videoIndex < videoURLs.length) {
				source.setAttribute('src', videoURLs[videoIndex]);
				video.load();
				video.play();
			} else {
				// Begin image slideshow
				video.removeEventListener('ended', nextVideo);
				video.removeChild(source);
				slideshow.removeChild(video);
				slideShow();
			}
		}
	} else {
		slideShow();
	}
}
// Play the slideshow; when complete, play the videos again. Note: URLs are currently hard-coded local paths
function slideShow() {
	var imageURLs = ["Exhibits/AlienRescue/images/img10.jpg", "Exhibits/AlienRescue/images/img1.jpg"]/* List of github image urls */
	if (imageURLs.length > 0) {
		var slideshow = document.getElementById("slideshow");
		var slide = document.createElement("img");
		slide.style.marginLeft = "auto";
		slide.style.marginRight = "auto";
		slide.style.display = "block";
		slide.style.height = "100%";
		var slideIndex = 0;
		slide.setAttribute('src', imageURLs[slideIndex]);
		slideshow.appendChild(slide);
		timer = setInterval(nextSlide, 3000);
		function nextSlide() {
			++slideIndex;
			if (slideIndex < imageURLs.length) {
				slide.setAttribute('src', imageURLs[slideIndex]);
			} else {
				// switch back to video playlist
				clearInterval(timer);
				slideshow.removeChild(slide);
				videoPlaylist();
			}
		}
	} else {
		videoPlaylist();
	}
}
</script>

<script>
// Runs when page is loaded. Initializes slideshow, etc.
var name = getExhibitName();
//loadImageURLs(name);
setTitle(name);
setDescription(name);
videoPlaylist();
</script>

</body>

</html>

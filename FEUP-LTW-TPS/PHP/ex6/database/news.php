<?php  
include_once ('connection.php');  
function getAllNews(){   

	global $db;  
	$stmt = $db->prepare('SELECT * from news');  
	$stmt->execute(); 
	$articles = $stmt->fetchAll();  
	return $articles;
}     
?>


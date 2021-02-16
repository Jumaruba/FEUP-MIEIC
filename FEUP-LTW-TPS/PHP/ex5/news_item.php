<?php  

$db = new PDO('sqlite:news.db');  

$stmt = $db->prepare('SELECT * FROM news JOIN users USING (username) where id= :id'); 
$stmt->bindParam(':id', $_GET['id'], PDO::PARAM_INT);
$stmt->execute(); 
$article = $stmt->fetch(); 

// Now I want to get comments from a specific news 

$stmt = $db->prepare('SELECT * FROM comments JOIN users USING (username) WHERE news_id = ?'); 
$stmt->execute(array($_GET['id'])); 
$comments  = $stmt->fetchAll();  
?>    

<html> 
	<head> 
	</head> 
	<body> 
	<h1> <?php echo $article['title'] ?> </h1>  
	<?php
	foreach ($comments as $comment){  
			printf("<p>%s</p>", $comment['text']);   
		}  
	?> 
	</body> 
</html> 






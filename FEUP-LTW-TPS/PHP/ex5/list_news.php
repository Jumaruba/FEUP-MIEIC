<html> 

<head> 
	<title> sqlite </title> 
</head> 
<body> 
<?php  

		$db = new PDO('sqlite:news.db');  
		$stmt = $db->prepare('SELECT * FROM news');  
		$stmt->execute(); 
		$articles = $stmt->fetchAll();   

		foreach($articles as $article){   
			echo $article['id']; 
			printf("<a href='news_item.php?id=%s'><h1>%s</h1></a>", $article['id'], $article['title']); 
			echo '<p>' .$article['introduction']. '</p>';
		} 

	?>
</body> 
</html>  

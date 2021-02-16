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

			echo '<h1>' .$article['title'] . '</h1>'; 
			echo '<p>' .$article['introduction']. '</p>';
			
		} 

	?>
</body> 
</html>  

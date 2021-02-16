<html>
<head> 
	<title> sqlite </title> 
</head> 
<body>  
<?php

    include_once('database/connection.php');
    include_once('database/news.php');
    $articles = getAllNews();
    include('template/common/header.php');
    foreach($articles as $article){
            echo $article['id'];
            printf("<a href='news_item.php?id=%s'><h1>%s</h1></a>", $article['id'], $article['title']);
            echo '<p>' .$article['introduction']. '</p>';
        }

    ?>
</body> 
</html> 

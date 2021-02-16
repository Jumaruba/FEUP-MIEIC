<?php  
include_once ('database/connection.php');
include_once ('database/comments.php');

    $comments = getComments();
?>

<html> 
	<head> 
	</head> 
	<body> 
	<?php
	foreach ($comments as $comment){  
			printf("<p>%s</p>", $comment['text']);   
		}  
	?> 
	</body> 
</html> 






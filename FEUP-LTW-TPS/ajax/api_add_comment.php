<?php  

include_once('database/comments.php'); 
include_once('database/connection.php'); 

$news_id = $_REQUEST["news_id"];  
$username = $_REQUEST['username']; 
$comment_id = $_REQUEST['comment_id']; 
$text = $_REQUEST['comment'];   


insertComment($news_id, $username, $text); 

$encoded = json_encode(array('news_id'=>$news_id, 'username' => $username, 
                    'comment_id' => $comment_id, "text" => $text)); 


echo $encoded;
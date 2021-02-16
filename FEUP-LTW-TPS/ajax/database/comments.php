<?php
  function getCommentsByNewId($id) {
    global $db;
    $stmt = $db->prepare('SELECT * FROM comments JOIN users USING (username) WHERE news_id = ?');
    $stmt->execute(array($id));
    return $stmt->fetchAll();
  } 

  function insertComment($news_id, $username, $text){
    global $db;
    $stmt = $db->prepare('INSERT INTO comments (news_id, published, username, text)
                          VALUES(?, 0, ?,?)');
    $stmt->execute(array($news_id, $username, $text));   

  
  }
?>
 


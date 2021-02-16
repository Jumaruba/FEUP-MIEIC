let commentForm = document.querySelector('form');   

commentForm.addEventListener("submit", submitComment); 

function encodeForAjax(data) {
    return Object.keys(data).map(function(k){
      return encodeURIComponent(k) + '=' + encodeURIComponent(data[k])
    }).join('&')
  } 

function submitComment(evt){
    evt.preventDefault();       // prevent the page to be reloaded  

    // Get information from form 
    let news_id  = document.querySelector('form input[name="id"]').value; 
    let username = document.querySelector('form input[name="username"]').value;  
    let comment = document.querySelector('form textarea').value;

    let comments_ids= document.querySelectorAll('#comments article.comment > span:first-child');
    let last_comment_id = comments_ids[comments_ids.length - 1].textContent;  
    let curr_comment_id = parseInt(last_comment_id) +1;  

    let request = new XMLHttpRequest();  
    request.addEventListener("load", receiveComments);   
    request.open("post", "api_add_comment.php", true);  
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');  
    request.send(encodeForAjax({'news_id': news_id, 'username': username, 'comment': comment, 'comment_id': curr_comment_id}));    

} 

function receiveComments(){      
  let comments = JSON.parse(this.responseText); 
  let list = document.getElementById("comments");  

  for (comment in comments){
    let item = document.createElement("article"); 
    item.className = "comment"; 
    item.innerHTML = ' <article class="comment"> ' + 
      '<span class="id">'+ comment.comment_id +'</span>' + 
      '<span class="user">'+ comment.username + '</span>' + 
      '<span class="date">'+ comment.date+'</span>'+  
      '<p>' + comment.text+'</p></article>';  
      list.appendChild(item);
  }


}
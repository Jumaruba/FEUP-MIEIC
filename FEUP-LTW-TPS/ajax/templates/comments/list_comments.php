<section id="comments">
  <h1><?=count($comments)?> Comment<?=count($comments)==1?'':'s'?></h1>
  <?php foreach ($comments as $comment) { ?>
    <article class="comment"> 
      <span class="id"><?=$comment['id']?></span>
      <span class="user"><?=$comment['name']?></span>
      <span class="date"><?=date('Y-m-d H:i:s', $comment['published']);?></span>
      <p><?=$comment['text']?></p>
    </article>
  <?php } ?>
  <form>
    <h2>Add your voice...</h2>
    <label>Username
      <input type="text" name="username">
    </label>
    <label>Comment
      <textarea name="text"></textarea>
    </label>
    <input type="hidden" name="id" value="<?=$article['id']?>">
    <input type="submit" value="Reply">
  </form>
</section>

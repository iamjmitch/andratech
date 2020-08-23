<?php include './inc/head.inc';?>
  <body>
    <div id="fullPage">
      <div id="landing">
      <?php include './inc/header.inc';?>
      <?php include './inc/hero.inc';?>
      </div>
      <?php include './inc/whyChooseUs.inc';?>
      <?php include './inc/banner1.inc';?>
      <?php include './inc/services.inc';?>
      <?php include './inc/banner2.inc';?>
      
      
      <?php require './inc/FBPosts.inc'; ?>
      <?php include './inc/getFBPost.inc';?>
      <?php include './inc/footer.inc';?>
    </div>
    <script src="./assets/js/app.js"></script> 
    <script src="https://unpkg.com/aos@2.3.1/dist/aos.js"></script>
    <script>
    AOS.init({
   easing: 'ease-in-out',
   duration: 300,
   delay: 400,
   once: true,
   
});
    </script>
    
      
</body>


</html>

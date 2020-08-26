<?php
require 'api.inc.php';

class FBPosts extends api
{
    protected $options;
    protected $url;
    protected $posts = "";

    public function __construct()
    {
        $this->options = "permalink_url,message,attachments";
        $this->url = "https://graph.facebook.com/andratechcomputing/feed?access_token=" . $this->accessToken . "&fields=" . $this->options;
    }

    //get list of facebook posts
    protected function getPostsList()
    {
        // var_dump(json_decode(file_get_contents($this->url) , true));
        return json_decode(file_get_contents($this->url) , true);
        
    }

    //validates the post to make sure only posts with a message are displayed. strips out updates like profile changes
    protected function postValidator()
    {
        $postList = $this->getPostsList();
        $validPosts = 0;
        for ($i = 0;$validPosts < 4;$i++)
        {
            $thisPost = $postList['data'][$i];
            if (isset($thisPost['message']))
            {
                $this->getPostType($thisPost);
                $validPosts += 1;
            }
            else
            {
                //post is skipped as we do not want to display it
                
            }
        }
    }

    //determine what type post is i.e message only, video, photo etc
    protected function getPostType($postData)
    {
        //if post has an image or video attached
        if (isset($postData['attachments']))
        {
            $this->postHasAttachment($postData);
        }
        else
        {
            //message only
            $this->postMessageOnly($postData);
        }
    }

    protected function postHasAttachment($postData)
    {
        $thisPost = $postData['attachments']['data'][0]['media'];
        //if post has video attached
        if (isset($thisPost['source']))
        {
            $this->postHasVideo($postData, $thisPost['source']);
        }
        //if post has images only attached
        else if (isset($thisPost['image']['src']))
        {
            $this->postHasImage($postData);
        }
        else
        {
            //fall back to message only incase different post type arises not considered when developing
            $this->postMessageOnly($postData);
        }
    }

    // function for if post has a video attached to post. Currently only youtube videos will embed a video on page
    protected function postHasVideo($postData, $videoLink)
    {   //will embed youtube video
        if ($this->isYoutube($videoLink))
        {
            $autoPlayRemove = strtok($videoLink, '?');
            $iframeWidth = "260";
            $iframeHeight = "260";
            $message = $this->messageHasLink($postData['message']);
            $cardMedia = '<iframe src="' . $autoPlayRemove . '?autoplay=0" frameborder="0" allowfullscreen width=' . $iframeWidth . ' height=' . $iframeHeight . '></iframe>';
            $this->cardMaker($cardMedia, $message);
            $this->messageHasLink($message);

        }
        else
        {   //for all other video posts such as FB video that have a different way of <iframe>. more video site functions to be added as needed
            $this->postHasImage($postData, true);

        }

    }

    
    // function for if post has an image attached.
    protected function postHasImage($postData, $isVideo = false)
    {
        $thisPost = $postData['attachments']['data'][0];
        $directLink = $thisPost['target']['url'];
        $tempImgLink = $thisPost['media']['image']['src'];
        $imageLink = $this->isImageBlank($tempImgLink, $postData['id']);
        $message = $this->messageHasLink($postData['message']);
        $cardMedia = '<a href="' . $directLink . '" target="_blank">
        <img src="' . $imageLink . '" alt="Facebook Post Image"> 
        </a>';
        $this->cardMaker($cardMedia, $message);

    }

    //function to download external images to server and redeploy with internal URI. Only exists because firefox wont display facebook images due to trackers    
    //uses facebook post-id to keep track of what is already in filesystem
    protected function saveImage($url, $id){
        $filename =  $id;
        $saveLocation = "./assets/img/tmp/" . $filename . ".jpg";
        //if file already exists and is less than 7 days old, dont re-download image, just return existing URI (7days == 168 hours, 3600 seconds in 1 hour)
        if (file_exists($saveLocation) && (time()-filemtime($saveLocation) < 168 * 3600)){
            return $saveLocation;            
        }else{        
            copy($url, $saveLocation);
            return $saveLocation;
        }
    }

   //function to strip the relevant data from the post object and pass to cardMaker() to output
    protected function postMessageOnly($postData)
    {
        $imgPath = './assets/img/default.jpg';
        $message = $this->messageHasLink($postData['message']);
        $cardMedia = '<img src="' . $imgPath . '" alt="Andratech Logo">';
        $this->cardMaker($cardMedia, $message);

    }

    // cardMaker takes the media and message generated by other functions, turns into a html card component and then add to global variable $posts
    protected function cardMaker($cardMedia, $message)
    {       
            $output = '<div class="card" data-aos="zoom-in">                        
                            <div class="cardMediaContainer">
                                ' . $cardMedia . '
                            </div>
                            <div class="cardMessage">
                            ' . ($message) . '
                            </div>
                            
                        </div>                           
                    ';  
        $this->posts = $this->posts . $output;

    }

    //helper functions
    protected function isYoutube($link)
    {
        //check if link string contains the word "youtube"
        return (strpos($link, 'youtube') !== false);

    }

    //checks to see if attached images is greater than 1px and if not returns a default image path. safe guard against broken links
    protected function isImageBlank($link, $id)
    {
        $getImageSize = getimagesize($link);
        $width = substr($getImageSize[3], 0, strpos($getImageSize[3], ' '));
        $width = preg_match_all('!\d+!', $width, $matches);
        $width = ($matches[0][0]) + 0;
        $return = "";
        if ($width <= 1)
        {
            $return = "./assets/img/default.jpg";
        }
        else
        {
            $return = $this->saveImage($link, $id);
        }
        return $return;
    }

    //scans link to see if a link id posted in message. if so converts to ahref
    protected function messageHasLink($message)
    {
        preg_match_all('#\bhttps?://[^,\s()<>]+(?:\([\w\d]+\)|([^,[:punct:]\s]|/))#', $message, $match);
        if (!empty($match[0]))
        {
            $start = strpos($message, $match[0][0]);
            $end = $start + strlen($match[0][0]);
            $ahref = '<br><br><a href="' . $match[0][0] . '" target="_blank">';
            $out = substr_replace($message, "</a>", $end, 0);
            $out = substr_replace($out, $ahref, $start, 0);
            return $out;
        }
        else
        {
            return $message;
        }
    }

    //go function
    public function getPosts()
    {
        $this->postValidator();
        echo $this->posts;
    }
}
?>

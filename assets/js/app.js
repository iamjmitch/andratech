function qs(elmt) {
  return document.querySelector(elmt);
}
function qsa(elmt) {
  return document.querySelectorAll(elmt);
}

window.onscroll = function () {
  navChange();
};

var navbar = qs('nav');
var smallLogo = qs('.hidden.left');
var sticky = navbar.offsetTop;
const BTTbtn = qs('#backToTop');

function navChange() {
  if (window.pageYOffset >= sticky) {
    navbar.classList.add('sticky');
    smallLogo.classList.add('showMiniLogo');
    smallLogo.classList.remove('hidden');
    BTTbtn.style.opacity = '1';
  } else {
    navbar.classList.remove('sticky');
    smallLogo.classList.remove('showMiniLogo');
    smallLogo.classList.add('hidden');
    BTTbtn.style.opacity = '0';
  }
}

//map setup & options
function initMap() {
  var coordinates = { lat: -27.2429453, lng: 152.9973342 };
  var map = new google.maps.Map(document.getElementById('map'), {
    zoom: 14,
    center: coordinates,
  });
  var marker = new google.maps.Marker({ position: coordinates, map: map });
}

//Back to Top Button

window.fbAsyncInit = function () {
  FB.init({
    appId: '300924894467707',
    xfbml: true,
    version: 'v8.0',
  });
  FB.AppEvents.logPageView();
};

(function (d, s, id) {
  var js,
    fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) {
    return;
  }
  js = d.createElement(s);
  js.id = id;
  js.src = 'https://connect.facebook.net/en_US/sdk.js';
  fjs.parentNode.insertBefore(js, fjs);
})(document, 'script', 'facebook-jssdk');

// function waitFB() {
//   if (typeof FB == 'undefined') {
//     setTimeout(waitFB, 1000);
//   } else {
//     fbLoad();
//   }
// }

// function fbLoad() {
//   var pageAccessToken =
//     'EAAERsIlwVnsBANLma0wYhoBdbmKhWwLbDmM716GiGRSzIhRztKiHmpCsH9pZB0Xu6f4eDr2ZAIILyeLoW68s0qZBwe3KI5bE71mVZATxuW3BQOPJapaZA8GyPZANspCCFeqaOcxkzVN0BnXginplLQpQLBBSZB2hi979Sd8tbAbEhev2v4YSsLCZAVzijOLw5ZBSukQ0OBx7SLmR17JM9RmCdADkTq9cPhkwZD';
//   FB.api(
//     '/me/feed?',
//     {
//       access_token: pageAccessToken,
//       fields: 'id, permalink_url',
//     },
//     function (response) {
//       console.log(response);
//     }
//   );
// }
// waitFB();

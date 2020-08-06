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

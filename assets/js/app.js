function qs(elmt) {
  return document.querySelector(elmt);
}

function qsa(elmt) {
  return document.querySelectorAll(elmt);
}

window.onscroll = function () {
  myFunction();
};

var navbar = qs('nav');
var smallLogo = qs('.hidden.left');
var sticky = navbar.offsetTop;

function myFunction() {
  if (window.pageYOffset >= sticky) {
    navbar.classList.add('sticky');
    smallLogo.classList.add('showMiniLogo');
    smallLogo.classList.remove('hidden');
  } else {
    navbar.classList.remove('sticky');
    smallLogo.classList.remove('showMiniLogo');
    smallLogo.classList.add('hidden');
  }
}

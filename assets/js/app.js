function qs(elmt) {
  return document.querySelector(elmt);
}

function qsa(elmt) {
  return document.querySelectorAll(elmt);
}

var head = qs('#fullLogoContainer');
var jumbo = qs('#hero');
var windowHeight = window.innerHeight;

jumbo.style.height = ((windowHeight - head.offsetHeight) -  + 'px';

window.addEventListener('DOMContentLoaded',function(){
    window.addEventListener('scroll', function() {
        let reveals = document.querySelectorAll(".reveal");
        for(var i=0;i<reveals.length;i++){
            let windowHeight = window.innerHeight;
            let revealTop = reveals[i].getBoundingClientRect().top;
            let revealPoint = 150;

            if(revealTop<windowHeight-revealPoint){
                reveals[i].classList.add('scrolled');
            }
            else{
                reveals[i].classList.remove('scrolled');
            }
        }
    });
    window.addEventListener('scroll', function(){
        let lid = document.querySelector('.lid');
        let laptop = document.querySelector('.laptop');
        let laptopRect = laptop.getBoundingClientRect();
        let scrollPosition = window.scrollY;

        let startClosingPosition = laptopRect.top + window.scrollY -200;

        let maxRotation = 90;
        let rotation = 0;

        if (scrollPosition > startClosingPosition) {
            rotation = Math.min((scrollPosition - startClosingPosition) / 2, maxRotation); // limit to maxRotation
        }

        lid.style.transform = `rotateX(${-rotation}deg) `;
    });
    window.addEventListener('scroll',function(){
        let myBtn = document.querySelector('#myButton');
        if(document.body.scrollTop>20 || document.documentElement.scrollTop>20){
            myBtn.style.display='block';
        }
        else{
            myBtn.style.display='none';
        }
    });
});
function Top(){
    window.scrollTo({top:0, behavior:'smooth'});
}

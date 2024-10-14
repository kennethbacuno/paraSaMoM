var historyBtn = document.getElementById("historyBtn");

function toggleLight() {
    const button = document.getElementById("lightBtn");
    if (button.innerHTML === "Off") {
        button.innerHTML = "On";
        button.style.backgroundColor = '#B9B7A7';
        button.style.color = '#000'
        button.setAttribute('href', '/lights_on');
    } else {
        button.innerHTML = "Off";
        button.style.backgroundColor = '#737373';
        button.style.color = '#fff'
        button.setAttribute('href', '/lights_off');
    }
}

function toggleLaser() {
    const button = document.getElementById("laserBtn");
    if (button.innerHTML === "Off") {
        button.innerHTML = "On";
        button.style.backgroundColor = '#B9B7A7';
        button.style.color = '#000'
        button.setAttribute('href', '/laser_on');
    } else {
        button.innerHTML = "Off";
        button.style.backgroundColor = '#737373';
        button.style.color = '#fff'
        button.setAttribute('href', '/laser_off');
    }
}

function toggleEntrance() {
    const button = document.getElementById("entranceBtn");
    if (button.innerHTML === "Closed") {
        button.innerHTML = "Open";
        button.style.backgroundColor = '#B9B7A7';
        button.style.color = '#000'
        button.setAttribute('href', '/entrance_servo_on');
    } else {
        button.innerHTML = "Closed";
        button.style.backgroundColor = '#737373';
        button.style.color = '#fff'
        button.setAttribute('href', '/entrance_servo_off');
    }
}

function toggleExit() {
    const button = document.getElementById("exitBtn");
    if (button.innerHTML === "Closed") {
        button.innerHTML = "Open";
        button.style.backgroundColor = '#B9B7A7';
        button.style.color = '#000'
        button.setAttribute('href', '/exit_servo_on');
    } else {
        button.innerHTML = "Closed";
        button.style.backgroundColor = '#737373';
        button.style.color = '#fff'
        button.setAttribute('href', '/exit_servo_off');
    }
}

function openNav() {
    document.querySelector(".image-button").style.display = "none";
    document.getElementById("mySidenav").classList.add("open");
    document.body.classList.add("push");
}

function closeNav() {
    document.querySelector(".image-button").style.display = "block";
    document.getElementById("mySidenav").classList.remove("open");
    document.body.classList.remove("push");
}

function navigateTo(sectionId) {
    // Hide all sections
    const sections = document.querySelectorAll('.content-section');
    sections.forEach(section => section.style.display = 'none');
    
    // Show the clicked section
    document.getElementById(sectionId).style.display = 'block';
    closeNav(); // Close the sidenav after navigating
}

// Show the homepage section by default
document.addEventListener("DOMContentLoaded", function() {
    navigateTo('Home');
});



        // Add a click event listener to the button
        historyBtn.addEventListener("click", function() {
            // Redirect to the new HTML file
            window.location.href = "history.html";
        });
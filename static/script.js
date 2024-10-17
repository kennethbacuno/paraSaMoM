var historyBtn = document.getElementById("historyBtn");

async function toggleLight() {
    const button = document.getElementById("lightBtn");
    const url = button.innerHTML === "Off" ? '/lights_on' : '/lights_off';
    const action = button.innerHTML === "Off" ? "On" : "Off";

    button.innerHTML = action;
    button.style.backgroundColor = action === "On" ? '#B9B7A7' : '#737373';
    button.style.color = action === "On" ? '#000' : '#fff';

    try {
        const response = await fetch(url, { method: 'GET' });
        const data = await response.json();
        console.log(data.message); // Optional: log the response message
    } catch (error) {
        console.error('Error:', error);
    }
}

async function toggleLaser() {
    const button = document.getElementById("laserBtn");
    const url = button.innerHTML === "On" ? '/laser_off' : '/laser_on';
    const action = button.innerHTML === "On" ? "Off" : "On";

    button.innerHTML = action;
    button.style.backgroundColor = action === "On" ? '#B9B7A7' : '#737373';
    button.style.color = action === "On" ? '#000' : '#fff';

    try {
        const response = await fetch(url, { method: 'GET' });
        const data = await response.json();
        console.log(data.message); // Optional: log the response message
    } catch (error) {
        console.error('Error:', error);
    }
}

async function toggleEntrance() {
    const button = document.getElementById("entranceBtn");
    const url = button.innerHTML === "Closed" ? '/entrance_servo_on' : '/entrance_servo_off';
    const action = button.innerHTML === "Closed" ? "Open" : "Closed";

    button.innerHTML = action;
    button.style.backgroundColor = action === "Open" ? '#B9B7A7' : '#737373';
    button.style.color = action === "Open" ? '#000' : '#fff';

    try {
        const response = await fetch(url, { method: 'GET' });
        const data = await response.json();
        console.log(data.message); // Optional: log the response message
    } catch (error) {
        console.error('Error:', error);
    }
}

async function toggleExit() {
    const button = document.getElementById("exitBtn");
    const url = button.innerHTML === "Closed" ? '/exit_servo_on' : '/exit_servo_off';
    const action = button.innerHTML === "Closed" ? "Open" : "Closed";

    button.innerHTML = action;
    button.style.backgroundColor = action === "Open" ? '#B9B7A7' : '#737373';
    button.style.color = action === "Open" ? '#000' : '#fff';

    try {
        const response = await fetch(url, { method: 'GET' });
        const data = await response.json();
        console.log(data.message); // Optional: log the response message
    } catch (error) {
        console.error('Error:', error);
    }
}

async function fetchCounter() {
    try {
        const response = await fetch('/get_counter');
        const data = await response.json();
        if (data.status === "success") {
            document.getElementById("counterDisplay").textContent = `${data.counter}/100`;
        } else {
            console.error("Failed to fetch counter:", data.message);
        }
    } catch (error) {
        console.error("Error:", error);
    }
}

// Fetch counter every 2 seconds
setInterval(fetchCounter, 500);

// Call fetchCounter initially to show the current counter on page load
fetchCounter();

async function fetchTemp() {
    try {
        const response = await fetch('/visitor_db');
        const data = await response.json();
        if (data.status === "success") {
            console.log("received_temp: ", data.message);
        } else {
            console.error("Failed to fetch counter:", data.message);
        }
    } catch (error) {
        console.error("Error:", error);
    }
}
fetchTemp();

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
document.addEventListener("DOMContentLoaded", function () {
    navigateTo('Home');
});



// Add a click event listener to the button
historyBtn.addEventListener("click", function () {
    // Redirect to the new HTML file
    window.location.href = "history.html";
});
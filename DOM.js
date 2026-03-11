let nameInput = document.getElementById("name");
let rollInput = document.getElementById("roll");
let addBtn = document.getElementById("addBtn");
let list = document.getElementById("studentList");
let totalText = document.getElementById("total");
let attendanceText = document.getElementById("attendance");
let searchInput = document.getElementById("search");



function checkInput() {
    if (nameInput.value.trim() !== "" && rollInput.value.trim() !== "")
        addBtn.disabled = false;
    else
        addBtn.disabled = true;
}

nameInput.addEventListener("input", checkInput);
rollInput.addEventListener("input", checkInput);



addBtn.addEventListener("click", function () {

    let name = nameInput.value.trim();
    let roll = rollInput.value.trim();

    let li = document.createElement("li");
    li.classList.add("student");

    let text = document.createElement("span");
    text.textContent = roll + " - " + name;

    li.appendChild(text);



    let presentBox = document.createElement("input");
    presentBox.type = "checkbox";

    presentBox.addEventListener("change", function () {

        if (presentBox.checked)
            li.classList.add("present");
        else
            li.classList.remove("present");

        updateAttendance();
    });

    li.appendChild(presentBox);



    let editBtn = document.createElement("button");
    editBtn.textContent = "Edit";
    editBtn.classList.add("editBtn");

    editBtn.onclick = function () {

        let parts = text.textContent.split(" - ");
        let currentRoll = parts[0];
        let currentName = parts[1];

        let newRoll = prompt("Enter new roll", currentRoll);
        let newName = prompt("Enter new name", currentName);

        if (newRoll && newName) {
            text.textContent = newRoll + " - " + newName;
        }
    }

    li.appendChild(editBtn);



    let deleteBtn = document.createElement("button");
    deleteBtn.textContent = "Delete";
    deleteBtn.classList.add("deleteBtn");

    deleteBtn.onclick = function () {

        if (confirm("Are you sure you want to delete this student?")) {
            li.remove();
            updateTotal();
            updateAttendance();
        }
    }

    li.appendChild(deleteBtn);


    list.appendChild(li);

    nameInput.value = "";
    rollInput.value = "";
    addBtn.disabled = true;

    updateTotal();
    updateAttendance();

});



function updateTotal() {
    let total = list.children.length;
    totalText.textContent = "Total students: " + total;
}



function updateAttendance() {

    let present = document.querySelectorAll(".present").length;
    let total = list.children.length;
    let absent = total - present;

    attendanceText.textContent = "Present: " + present + " , Absent: " + absent;
}



searchInput.addEventListener("input", function () {

    let search = searchInput.value.toLowerCase();
    let students = list.getElementsByTagName("li");

    for (let i = 0; i < students.length; i++) {

        let text = students[i].textContent.toLowerCase();

        if (text.includes(search))
            students[i].style.display = "flex";
        else
            students[i].style.display = "none";
    }

});



document.getElementById("sortBtn").addEventListener("click", function () {

    let items = Array.from(list.children);

    items.sort(function (a, b) {

        let textA = a.querySelector("span").textContent;
        let textB = b.querySelector("span").textContent;

        let nameA = textA.split(" - ")[1].toLowerCase();
        let nameB = textB.split(" - ")[1].toLowerCase();

        return nameA.localeCompare(nameB);

    });

    items.forEach(function (item) {
        list.appendChild(item);
    });

});



document.getElementById("highlightBtn").addEventListener("click", function () {

    let items = list.children;

    for (let i = 0; i < items.length; i++) {
        items[i].classList.remove("highlight");
    }

    if (items.length > 0)
        items[0].classList.add("highlight");

});
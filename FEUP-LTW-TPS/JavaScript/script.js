/*window.addEventListener('load', function(){
    let products = document.getElementById('products');
    console.log(products);
});*/

/*
// adding defer to the html
let products  = document.getElementById('products');
console.log(products);*/


let form_ = document.getElementsByTagName('form')[0];
let table_ = document.querySelector('table');
let allInputs;

table_.addEventListener('change', function() {
    let footer = document.getElementsByTagName('footer')[0];
    let span = footer.getElementsByTagName('span')[0];
    console.log(span.value);
});

form_.addEventListener('submit', function () {
    console.log(table_);
    getFormWithQueryAll();
    addNewLine();
});


function getFormWithTag() {
    console.log("TAG: FORM");
    let form = document.getElementsByTagName('form')[0];        // TagName return all the tag names
}

function getFormWithQuery() {
    console.log("QUERY SELECTOR: FORM");
    let secondInput = document.querySelectorAll('input')[1].value;
    console.log(secondInput);
}

function getFormWithQueryAll() {
    allInputs = {description: [], quantity: []};
    let allElements = document.querySelectorAll('form input');
    for (let i = 0; i < allElements.length - 1; i++)
        allInputs[allElements[i].getAttribute('name')].push(allElements[i].value);
}


function addNewLine() {
    let firstKey = Object.keys(allInputs)[0];
    let numbElements = allInputs[firstKey].length;
    let table = document.getElementById('products');

    for (let i = 0 ; i < numbElements; i++)
    {
        let newLine = document.createElement('tr');
        newLine.innerHTML = "<td>" + allInputs['description'][i] + "</td><td><input value=" + allInputs['quantity'][i] + "></td><td><input type='button' value= 'Remove'></td></tr>";
        newLine.getElementsByTagName('td')[2].addEventListener('click', removeElement);
        table.append(newLine);
    }

}

function removeElement(){
    this.parentNode.remove();
}
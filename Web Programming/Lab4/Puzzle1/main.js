const TABLE_ID = "numbers_puzzle";
const NUM_ROWS = document.getElementById(TABLE_ID).rows.length;
const NUM_COLUMNS = document.getElementById(TABLE_ID).rows[0].cells.length;

function randInt(high)
{
  return Math.floor(Math.random() * high);
}

function randomRange(low, high)
{
  return Math.floor(Math.random() * high) + low;
}

function insertContentIntoCell(tableID, rowID, columnID, content)
{
  document.getElementById(tableID).rows[rowID].cells[columnID].innerHTML = content == 0 ? "" : content;
}

function getCellContent(tableID, rowID, columnID)
{
  return document.getElementById(tableID).rows[rowID].cells[columnID].innerHTML;
}

function generateArray(n)
{
  return Array.from(Array(n).keys());
}

function shuffle(array)
{
  return array.sort(() => Math.random() - 0.5);
}

function initializeTable(tableID, numRows, numColumns)
{
  pool = generateArray(numRows * numColumns);
  generateArray(numRows).forEach(i => {
    generateArray(numColumns).forEach(j => {
        elem = pool[randInt(pool.length)];
        insertContentIntoCell(tableID, i, j, elem);
        pool.splice(pool.indexOf(elem), 1);
    });
  });
}

function drag(ev)
{
  ev.dataTransfer.setData("text", ev.target.id);
}

function allowDrop(ev)
{
  ev.preventDefault();
}

function drop(ev)
{
  ev.preventDefault();
  const data = ev.dataTransfer.getData("text");
  if(data != "" && (ev.target.innerHTML == "" || document.getElementById(data).innerHTML == ""))
  {
    const content = ev.target.innerHTML;
    ev.target.innerHTML=document.getElementById(data).innerHTML;
    document.getElementById(data).innerHTML = content;
    if(checkSolution(TABLE_ID, NUM_ROWS, NUM_COLUMNS) == true)
    {
      alert("You won!");
    }
  }
}

function checkSolution(tableID, numRows, numColumns)
{
  var solution = true;
  generateArray(numRows * numColumns - 1).forEach(i => {
    currentRow = Math.floor(i / numColumns);
    currentColumn = i % numColumns;
    nextRow = Math.floor((i + 1) / numColumns);
    nextColumn = (i + 1) % numColumns;

    cellContent1 = getCellContent(tableID, currentRow, currentColumn);
    cellContent2 = getCellContent(tableID, nextRow, nextColumn);
    if(cellContent1 != "" && cellContent2 != "")
    {
      if(parseInt(cellContent2) - parseInt(cellContent1) != 1)
      {
        solution = false;
      }
    }
  });
  return solution;
}

initializeTable("numbers_puzzle", NUM_ROWS, NUM_COLUMNS);

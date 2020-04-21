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
  document.getElementById(tableID).rows[rowID].cells[columnID].getElementsByTagName("img")[0].src = content == "0.png" ? "blank.png" : content;
  document.getElementById(tableID).rows[rowID].cells[columnID].getElementsByTagName("img")[0].id = rowID.toString() + "." + columnID.toString();
}

function getCellContent(tableID, rowID, columnID)
{
  var source = document.getElementById(tableID).rows[rowID].cells[columnID].getElementsByTagName("img")[0].src;
  var substr =  source.substring(source.length - 6, source.length - 4);
  if(substr[0] == '/')
  {
    return substr.slice(1, 2);
  }
  return substr;
}

function generateArray(n)
{
  return Array.from(Array(n).keys());
}

function initializeTable(tableID, numRows, numColumns)
{
  pool = generateArray(numRows * numColumns);
  generateArray(numRows).forEach(i => {
    generateArray(numColumns).forEach(j => {
        elem = pool[randInt(pool.length)];
        insertContentIntoCell(tableID, i, j, elem+".png");
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
  src1 = ev.target.src;
  src2 = document.getElementById(data).src;
  if(data != "" && (src1.endsWith("blank.png") || src2.endsWith("blank.png")))
  {
    ev.target.src = src2;
    document.getElementById(data).src = src1;
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
    if(cellContent1 != "nk" && cellContent2 != "nk")
    {
      if(parseInt(cellContent2) - parseInt(cellContent1) != 1)
      {
        solution = false;
      }
    }
  });
  return solution;
}

initializeTable("numbers_puzzle", 4, 4);

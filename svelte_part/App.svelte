<script>
  import { tableH, tableB } from "./store";
  import DataTbl from "./DataTbl.svelte";
  let name = "SELECT top 100 MenuChar, MenuDescr, state FROM ACTIVE_MENU;";

  function fLoadData() {
    // Define the URL to which you want to make the POST request
    const url = "http://localhost:5000/data";

    // Data to be sent in the POST request (can be a JSON object, FormData, etc.)

    // Configure the fetch options, including method, headers, and body for a POST request
    const options = {
      method: "POST",
      headers: {
        "Content-Type": "text/plain", // Set the content type based on your API requirements
        // You may need to include additional headers like authorization tokens, etc.
      },
      body: name, // Convert the data to a JSON string for the request body
    };

    let thBody = [];
    let thD = [];

    // Use the fetch function to make the POST request
    fetch(url, options)
      .then((response) => {
        // Check if the request was successful (status code in the range 200-299)
        if (!response.ok) {
          throw new Error(`HTTP error! Status: ${response.status}`);
        }

        return response.text();
      })
      .then((data) => {
        //console.log("Success:", data);

        let rowsArray = data.split("\n");
        let nrRows = rowsArray.length;
        for (var r = 0; r < nrRows; r++) {
          let oneRowArr = rowsArray[r].split("\t");
          if (r == 0) {
            for (var c = 0; c < oneRowArr.length; c++) thD.push(oneRowArr[c]);
          } else {
            let thBodyRow = [];

            for (var c = 0; c < oneRowArr.length; c++)
              thBodyRow.push(oneRowArr[c]);

            thBody.push(thBodyRow);
          }
        }

        tableB.set(thBody);
        tableH.set(thD);
      })
      .catch((error) => {
        // Handle errors during the fetch or server-side errors
        console.error("Error:", error);
      });
  }
</script>

<main>
  <textarea bind:value={name} />
  <hr />
  <button on:click={() => fLoadData()}>Exec</button>
  <DataTbl tbl_data_cols={$tableH} tbl_data_rows={$tableB} />
</main>

<style>
  textarea {
    width: 90%;
    margin-left: 5%;
    height: 80px;
  }
</style>

<script>
  import { tableH, tableB } from "./store";
  import DataTbl from "./DataTbl.svelte";
  let name = 'SELECT top 100 MenuChar, MenuDescr, state FROM ACTIVE_MENU;';

  function fLoadData() {
    const data = {
      sql: name
    };

    fetch("http://localhost:5000/data", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(data),
    })
      .then((response) => response.text())
      .then((json_data) => {
        console.log(json_data); // Output the server response

        // Parse the JSON string into a JavaScript array of objects
        var parsed_data = JSON.parse(json_data);

        console.log(parsed_data);
        let thBody = [];
        let thD = [];
        // Access the properties of each object in the array using a for loop
        for (var i = 0; i < parsed_data.length; i++) {
          var data = parsed_data[i];
          if (i == 0) {
            for (var key in data) {
              console.log(key + ": " + data[key]);
              thD.push(data[key]);
            }
          } else {
            let thBodyr = [];
            for (var key in data) {
              thBodyr.push(data[key]);
            }
            thBody.push(thBodyr);
          }
        }

        tableB.set(thBody);
        tableH.set(thD);
        //	document.getElementById('demo').innerText = json_data;
      })
      .catch((error) => {
        console.error("Error:", error);
      });
  }
</script>

<main>

  <textarea bind:value={name} /><hr>
  <button on:click={() => fLoadData()}>Exec</button>
  <DataTbl tbl_data_cols={$tableH} tbl_data_rows={$tableB} />
</main>

<style>
	textarea {
		width: 90%;
    margin-top: auto;
		height: 80px;
	}
</style>

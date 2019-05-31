open Opium.Std;

let auth_header =
  post("/auth", req => {
    let result =
      switch (Cohttp.Header.get(req |> Request.headers, "Authorization")) {
      | Some(a) => a
      | None => "None"
      };

    `String(result) |> respond';
  });

let hello_param =
  get("/hello/:name", req =>
    `String("Hello " ++ param(req, "name")) |> respond'
  );

let json_response =
  get("/json", _req => {
    let json =
      Ezjsonm.(
        dict([("name", string("Elizabeth")), ("height", int(163))])
      );

    `Json(json) |> respond';
  });

let _ =
  App.empty |> auth_header |> hello_param |> json_response |> App.run_command;

open Opium.Std;

let auth_header =
  post("/auth", req => {
    let result =
      switch (Cohttp.Header.get(req |> Request.headers, "Authorization")) {
      | Some(auth) => auth
      | None => "None"
      };

    `String(result) |> respond';
  });

let hello_param =
  get("/hello/:name", req =>
    `String("Hello " ++ param(req, "name")) |> respond'
  );

let hello_world =
  get("/", _req => `Html("<h1>Hello World!</h1>") |> respond');

let json_response =
  get("/json", _req => {
    let json =
      `Assoc(
        ([("name", `String("Elizabeth")), ("height", `Int(163))])
      );

    `Json(json) |> respond';
  });

let _ =
  App.empty
  |> auth_header
  |> hello_param
  |> json_response
  |> hello_world
  |> App.run_command;

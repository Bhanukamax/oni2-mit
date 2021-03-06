open Revery;
open Revery.UI;
open Oni_Core;
open Oni_Model;
open Oni_Core.Types.UiFont;

let component = React.component("commandline");

/* let cmdFontSize = 15; */
let cmdFontColor = Colors.white;

/*
   TODO: Flow text around a "cursor"
 */

let getStringParts = (index, str) =>
  switch (index) {
  | 0 => ("", str)
  | _ =>
    let strBeginning = Str.string_before(str, index);
    let strEnd = Str.string_after(str, index);
    (strBeginning, strEnd);
  };

let createElement =
    (~children as _, ~command: Commandline.t, ~theme: Theme.t, ()) =>
  component(hooks => {
    let uiFont = State.(GlobalContext.current().state.uiFont);
    let {fontFile, _} = uiFont;
    let fontSize_ = 14;

    let textStyles =
      Style.[
        fontFamily(fontFile),
        fontSize(fontSize_),
        color(cmdFontColor),
        textWrap(TextWrapping.WhitespaceWrap),
      ];

    let (startStr, endStr) =
      getStringParts(command.position, command.content);
    command.show
      ? (
        hooks,
        <View
          style=Style.[
            width(400),
            overflow(`Hidden),
            backgroundColor(theme.colors.editorBackground),
            flexDirection(`Row),
            alignItems(`Center),
            marginBottom(20),
            paddingVertical(8),
            boxShadow(
              ~xOffset=-15.,
              ~yOffset=5.,
              ~blurRadius=30.,
              ~spreadRadius=5.,
              ~color=Color.rgba(0., 0., 0., 0.2),
            ),
          ]>
          <Text
            style=Style.[marginLeft(10), ...textStyles]
            text={command.firstC ++ startStr}
          />
          <View
            style=Style.[
              width(2),
              height(fontSize_),
              backgroundColor(cmdFontColor),
            ]
          />
          <Text style=textStyles text=endStr />
        </View>,
      )
      : (hooks, React.listToElement([]));
  });

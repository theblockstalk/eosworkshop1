async function stringTosha256() {
    const text = $("#string").val();
    const hash = await sha256(text);
    $("#hashOfString").attr("placeholder", hash);
}
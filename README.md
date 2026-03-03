# downloadIt

A small Qt/QML desktop application that downloads a YouTube video as an MP3 audio file.

## What it does

1. **User interface** (`DownloadIt.qml`): Displays a simple window with a text field (pre-filled with a YouTube video ID) and a "Download It" button.

2. **Request MP3 link** (`CDownloader::requestLink`): When the button is clicked the YouTube video ID is sent to the `youtubeinmp3.com` API endpoint:
   ```
   http://www.youtubeinmp3.com/fetch/?format=text&video=https://www.youtube.com/watch?v=<ID>
   ```
   The API responds with plain text in the form `Link: <download-url>`.

3. **Parse the response** (`CDownloader::getLinkForDownload`): The response text is split on `"Link: "` to extract the actual MP3 download URL.

4. **Download the MP3** (`CDownloader::downloadFile`): An HTTP GET request is made to the extracted URL (redirects are followed automatically).

5. **Save the file** (`CDownloader::onDownloaded` / `CDownloader::saveAs`): Once the download finishes the MP3 data is written to a local file named `30_m.mp3` (this filename is currently hardcoded as a placeholder — the original code has a `getFileName()` call commented out).

## Technology

- **Qt 5** (Qt Quick / QML for the UI, `QNetworkAccessManager` for HTTP)
- Language: C++ with QML

## Building

Open `DownloadIt.pro` in Qt Creator (or run `qmake` + `make`) and build the project.

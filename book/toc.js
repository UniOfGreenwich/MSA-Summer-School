// Populate the sidebar
//
// This is a script, and not included directly in the page, to control the total size of the book.
// The TOC contains an entry for each page, so if each page includes a copy of the TOC,
// the total size of the page becomes O(n**2).
class MDBookSidebarScrollbox extends HTMLElement {
    constructor() {
        super();
    }
    connectedCallback() {
        this.innerHTML = '<ol class="chapter"><li class="chapter-item affix "><li class="spacer"></li><li class="chapter-item affix "><li class="spacer"></li><li class="chapter-item affix "><li class="part-title">Main</li><li class="chapter-item "><a href="Introduction/Introduction.html"><strong aria-hidden="true">1.</strong> Introduction</a></li><li class="chapter-item "><a href="SelfStudy/SelfStudy.html"><strong aria-hidden="true">2.</strong> Self Study</a></li><li class="chapter-item "><a href="ProjOverview/ProjOverview.html"><strong aria-hidden="true">3.</strong> Project Overview</a></li><li class="chapter-item "><a href="ProjMgmt/ProjMmgt.html"><strong aria-hidden="true">4.</strong> Project Management</a></li><li class="chapter-item "><a href="CriticalPath/CriticalPath.html"><strong aria-hidden="true">5.</strong> Critcial Path</a></li><li class="chapter-item "><a href="Documentation/Documentation.html"><strong aria-hidden="true">6.</strong> Documentation</a></li><li class="chapter-item "><a href="CDSim/CDSim.html"><strong aria-hidden="true">7.</strong> Circuit Design and Simulation</a><a class="toggle"><div>❱</div></a></li><li><ol class="section"><li class="chapter-item "><a href="CDSim/OpAmps.html"><strong aria-hidden="true">7.1.</strong> OpAmps</a></li><li class="chapter-item "><a href="CDSim/MOSFETS.html"><strong aria-hidden="true">7.2.</strong> MOSFETS</a></li><li class="chapter-item "><a href="CDSim/Filters.html"><strong aria-hidden="true">7.3.</strong> Filters</a></li></ol></li><li class="chapter-item "><a href="Soldering/Soldering_Instructions.html"><strong aria-hidden="true">8.</strong> Soldering Instructions</a></li><li class="chapter-item "><a href="ESP8266/ESP8266.html"><strong aria-hidden="true">9.</strong> ESP8266</a><a class="toggle"><div>❱</div></a></li><li><ol class="section"><li class="chapter-item "><a href="ESP8266/Set_Up.html"><strong aria-hidden="true">9.1.</strong> ESP8266</a></li><li class="chapter-item "><a href="ESP8266/Testing_Sensors.html"><strong aria-hidden="true">9.2.</strong> Testing Sensors</a><a class="toggle"><div>❱</div></a></li><li><ol class="section"><li class="chapter-item "><a href="ESP8266/Temperature.html"><strong aria-hidden="true">9.2.1.</strong> Temperature</a></li><li class="chapter-item "><a href="ESP8266/Photo_Interrupter.html"><strong aria-hidden="true">9.2.2.</strong> Photo Interrupter</a></li><li class="chapter-item "><a href="ESP8266/Accelerometer.html"><strong aria-hidden="true">9.2.3.</strong> Accelerometer</a></li></ol></li><li class="chapter-item "><a href="ESP8266/IoT_Setup.html"><strong aria-hidden="true">9.3.</strong> IoT Setup</a></li><li class="chapter-item "><a href="ESP8266/Build_WebPage.html"><strong aria-hidden="true">9.4.</strong> Build Webpage</a></li><li class="chapter-item "><a href="ESP8266/Upload_Running.html"><strong aria-hidden="true">9.5.</strong> Upload and Running</a></li></ol></li><li class="chapter-item "><a href="Debian_Rock/Debian_Rock.html"><strong aria-hidden="true">10.</strong> Debian Rock C4</a><a class="toggle"><div>❱</div></a></li><li><ol class="section"><li class="chapter-item "><a href="Debian_Rock/Internet.html"><strong aria-hidden="true">10.1.</strong> Internet</a></li><li class="chapter-item "><a href="Debian_Rock/Workbook.html"><strong aria-hidden="true">10.2.</strong> Updating Workbook</a></li><li class="chapter-item "><a href="Debian_Rock/IoT_Network.html"><strong aria-hidden="true">10.3.</strong> IoT Network</a></li><li class="chapter-item "><a href="Debian_Rock/Python_Script.html"><strong aria-hidden="true">10.4.</strong> Python Script</a></li><li class="chapter-item "><a href="Debian_Rock/WireShark.html"><strong aria-hidden="true">10.5.</strong> WireShark</a></li></ol></li><li class="chapter-item "><a href="Security_IoT/Security_IoT.html"><strong aria-hidden="true">11.</strong> Security IoT</a><a class="toggle"><div>❱</div></a></li><li><ol class="section"><li class="chapter-item "><a href="Security_IoT/Case_Study.html"><strong aria-hidden="true">11.1.</strong> Case Study</a></li></ol></li><li class="chapter-item "><a href="Data_Analysis/Data_Analysis.html"><strong aria-hidden="true">12.</strong> Data Analysis</a></li></ol>';
        // Set the current, active page, and reveal it if it's hidden
        let current_page = document.location.href.toString();
        if (current_page.endsWith("/")) {
            current_page += "index.html";
        }
        var links = Array.prototype.slice.call(this.querySelectorAll("a"));
        var l = links.length;
        for (var i = 0; i < l; ++i) {
            var link = links[i];
            var href = link.getAttribute("href");
            if (href && !href.startsWith("#") && !/^(?:[a-z+]+:)?\/\//.test(href)) {
                link.href = path_to_root + href;
            }
            // The "index" page is supposed to alias the first chapter in the book.
            if (link.href === current_page || (i === 0 && path_to_root === "" && current_page.endsWith("/index.html"))) {
                link.classList.add("active");
                var parent = link.parentElement;
                if (parent && parent.classList.contains("chapter-item")) {
                    parent.classList.add("expanded");
                }
                while (parent) {
                    if (parent.tagName === "LI" && parent.previousElementSibling) {
                        if (parent.previousElementSibling.classList.contains("chapter-item")) {
                            parent.previousElementSibling.classList.add("expanded");
                        }
                    }
                    parent = parent.parentElement;
                }
            }
        }
        // Track and set sidebar scroll position
        this.addEventListener('click', function(e) {
            if (e.target.tagName === 'A') {
                sessionStorage.setItem('sidebar-scroll', this.scrollTop);
            }
        }, { passive: true });
        var sidebarScrollTop = sessionStorage.getItem('sidebar-scroll');
        sessionStorage.removeItem('sidebar-scroll');
        if (sidebarScrollTop) {
            // preserve sidebar scroll position when navigating via links within sidebar
            this.scrollTop = sidebarScrollTop;
        } else {
            // scroll sidebar to current active section when navigating via "next/previous chapter" buttons
            var activeSection = document.querySelector('#sidebar .active');
            if (activeSection) {
                activeSection.scrollIntoView({ block: 'center' });
            }
        }
        // Toggle buttons
        var sidebarAnchorToggles = document.querySelectorAll('#sidebar a.toggle');
        function toggleSection(ev) {
            ev.currentTarget.parentElement.classList.toggle('expanded');
        }
        Array.from(sidebarAnchorToggles).forEach(function (el) {
            el.addEventListener('click', toggleSection);
        });
    }
}
window.customElements.define("mdbook-sidebar-scrollbox", MDBookSidebarScrollbox);

#include <unistd.h>

#include "gpsd.h"

unsigned int my_alarm(unsigned int timeout, alarm_callback callback);

unsigned int my_alarm(unsigned int timeout, alarm_callback callback)
{
#if defined(S_SPLINT_S) || (defined(HAVE_ALARM) && defined(SIGALRM))
    if (callback) {
	(void)signal(SIGALRM, callback);
	(void)alarm(timeout);
    } else {
	(void)signal(SIGALRM, SIG_IGN);
    }
#elif defined(_WIN32)
    if (callback) {
	(void)SetTimer(NULL, 0, 1000 * timeout, callback);
    } else {
	(void)KillTimer(NULL, 0);
    }
#else /* !S_SPLINT_S && !(HAVE_ALARM && SIGALRM) && !_WIN32 */
#error "I cannot figure out how on this system to set an alarm timeout"
#endif /* !S_SPLINT_S && !(HAVE_ALARM && SIGALRM) && !_WIN32 */
    /* TODO: propogate errors */
    return 0;
}